#include "Hooks.h"
#include "Globals.h"
DrawModelExecuteFn oDrawModelExecute;

void ForceMaterial(IMaterial* material, Color color)
{
	if (material != nullptr)
	{
		RenderView->SetColorModulation(color.Base());
		ModelRender->ForcedMaterialOverride(material);
	}
}

Color espColors;
void __stdcall Game::DrawModelExecute(void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld)
{
	Hooks::pModel->UnHook();
	if (Engine->IsInGame() && Global::LocalPlayer)
	{
		if (info.pModel)
		{
			std::string modelName = ModelInfo->GetModelName(info.pModel);

			if (modelName.find(XorStr("models/player")) != std::string::npos && Options.Visuals.Chams.Enabled)
			{
				auto pModelEntity = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(info.entity_index));
				if (pModelEntity && pModelEntity->GetAlive() && !pModelEntity->GetDormant() && pModelEntity->GetTeam() != Global::LocalPlayer->GetTeam() && (pModelEntity->GetTeam() == 2 || pModelEntity->GetTeam() == 3))
				{

					if (pModelEntity->GetTeam() == 2)
						espColors = Color(int(Options.Visuals.Chams.EnemyColor[0]), int(Options.Visuals.Chams.EnemyColor[1]), int(Options.Visuals.Chams.EnemyColor[2]));
					else if (pModelEntity->GetTeam() == 3)
						espColors = Color(int(Options.Visuals.Chams.EnemyColor[0]), int(Options.Visuals.Chams.EnemyColor[1]), int(Options.Visuals.Chams.EnemyColor[2]));


					if (Options.Visuals.Chams.XQZ)
					{

						if (pModelEntity->GetTeam() == 2)
							espColors = Color(int(Options.Visuals.Chams.EnemyColorWall[0]), int(Options.Visuals.Chams.EnemyColorWall[1]), int(Options.Visuals.Chams.EnemyColorWall[2]));
						else if (pModelEntity->GetTeam() == 3)
							espColors = Color(int(Options.Visuals.Chams.EnemyColorWall[0]), int(Options.Visuals.Chams.EnemyColorWall[1]), int(Options.Visuals.Chams.EnemyColorWall[2]));

						ForceMaterial(Options.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, espColors);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

						if (Options.Visuals.Chams.Mode == 0)
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						else
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					}

					if (Options.Visuals.Chams.Mode == 0)
						visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					else
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

					ForceMaterial(Options.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, espColors);
					ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
				}
			}

			else if (modelName.find(XorStr("flash")) != std::string::npos && Options.Visuals.Removals.Flash)
			{
				IMaterial* flash = MaterialSystem->FindMaterial(XorStr("effects\\flashbang"), XorStr(TEXTURE_GROUP_CLIENT_EFFECTS));
				IMaterial* flashWhite = MaterialSystem->FindMaterial(XorStr("effects\\flashbang_white"), XorStr(TEXTURE_GROUP_CLIENT_EFFECTS));
				flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				ModelRender->ForcedMaterialOverride(flash);
				ModelRender->ForcedMaterialOverride(flashWhite);
			}

			else if (modelName.find(XorStr("arms")) != std::string::npos && Options.Visuals.Removals.Hands)
			{
				IMaterial* Hands = MaterialSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
				Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				ModelRender->ForcedMaterialOverride(Hands);
			}

			else if (modelName.find(XorStr("weapon")) != std::string::npos && Options.Visuals.Removals.Weapon)
			{
				if (!(modelName.find(XorStr("arms")) != std::string::npos))
				{
					IMaterial* Weapon = MaterialSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
					Weapon->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					ModelRender->ForcedMaterialOverride(Weapon);
				}
			}
			else if (modelName.find(XorStr("arms")) != std::string::npos && Options.Visuals.Removals.WireframeHands)
			{
				IMaterial* HandsWire = MaterialSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
				HandsWire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				ModelRender->ForcedMaterialOverride(HandsWire);
			}

			else if (modelName.find(XorStr("weapon")) != std::string::npos && Options.Visuals.Removals.WireframeWep)
			{
				if (!(modelName.find(XorStr("arms")) != std::string::npos))
				{
					IMaterial* WeaponWire = MaterialSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
					WeaponWire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
					ModelRender->ForcedMaterialOverride(WeaponWire);
				}
			}
		}
	}
	ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
	ModelRender->ForcedMaterialOverride(nullptr);
	Hooks::pModel->ReHook();
}