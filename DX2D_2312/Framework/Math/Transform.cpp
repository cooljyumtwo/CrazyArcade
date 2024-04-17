#include "Framework.h"

Transform::Transform()
{
	world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
	S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(localRotation.x, localRotation.y, localRotation.z);
	T = XMMatrixTranslation(localPosition.x, localPosition.y, 0.0f);
	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(nullptr, P);

	world = IP * S * R * T * P;

	if (parent)
		world *= parent->world;// world = world * parnet->world

	XMStoreFloat4x4(&matWorld, world);
	right = Vector2(matWorld._11, matWorld._12);
	up = Vector2(matWorld._21, matWorld._22);

	XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	XMStoreFloat2(&globalPosition, outT);
	XMStoreFloat2(&globalScale, outS);
}

void Transform::RenderUI()
{
	if (ImGui::TreeNode((tag + "_Transform").c_str()))
	{
		ImGui::Checkbox("Active", &isActive);

		ImGui::DragFloat2("Pos", (float*)&localPosition, 1.0f);

		Float3 rot;
		rot.x = XMConvertToDegrees(localRotation.x);
		rot.y = XMConvertToDegrees(localRotation.y);
		rot.z = XMConvertToDegrees(localRotation.z);

		ImGui::DragFloat3("Rot", (float*)&rot, 0.1f, -180.0f, 180.0f);

		localRotation.x = XMConvertToRadians(rot.x);
		localRotation.y = XMConvertToRadians(rot.y);
		localRotation.z = XMConvertToRadians(rot.z);

		ImGui::DragFloat2("Scale", (float*)&localScale, 0.1f);

		if (ImGui::Button("Save"))
			Save();

		if (ImGui::Button("Load"))
			Load();

		ImGui::TreePop();
	}
}

void Transform::Save()
{
	BinaryWriter* writer = new BinaryWriter("ResourcesCA/TextData/Transforms/" + tag + ".srt");

	writer->Float(localPosition.x);
	writer->Float(localPosition.y);

	writer->Float(localRotation.x);
	writer->Float(localRotation.y);
	writer->Float(localRotation.z);

	writer->Float(localScale.x);
	writer->Float(localScale.y);

	delete writer;
}

void Transform::Load()
{
	BinaryReader* reader = new BinaryReader("ResourcesCA/TextData/Transforms/" + tag + ".srt");

	if (reader->IsFailed())
		return;

	localPosition.x = reader->Float();
	localPosition.y = reader->Float();

	localRotation.x = reader->Float();
	localRotation.y = reader->Float();
	localRotation.z = reader->Float();

	localScale.x = reader->Float();
	localScale.y = reader->Float();

	delete reader;
}

bool Transform::IsActive()
{
	if (parent == nullptr)
		return isActive;

	if (isActive == false)
		return false;

	return parent->IsActive();
}

void Transform::SetGlobalPosition(Vector2 pos)
{
	if (parent)
		localPosition = pos * XMMatrixInverse(nullptr, parent->world);
	else
		localPosition = pos;

	UpdateWorld();
}
