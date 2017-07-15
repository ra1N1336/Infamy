#pragma once
enum TriggerFilters
{
	FILTER_NONE,
	FILTER_MOSTDAMAGE,
	FILTER_BODYONLY,
	FILTER_BODYNOARMS,
	FILTER_HEADONLY,
	FILTER_ARMSONLY
};

class cOptions
{
public:
	struct
	{
		struct
		{
			float 	TeamColor[3];
		}Glow;
		struct
		{
			bool Enabled;
			bool Enab;
			int 	Mode;
			bool	XQZ;
			float 	TeamColor[3];
			float 	TeamColorWall[3];
			float  	EnemyColor[3];
			float 	EnemyColorWall[3];
			bool TeamCheck;
		}Chams;
		struct
		{
			bool	Hands;
			bool	WireframeHands;
			bool	Weapon;
			bool	WireframeWep;
			bool	VisualRecoil;
			bool	Flash;
			bool    Smoke;
			bool	Sky;
			bool    Recoil;
			bool	NoSmoke;
		} Removals;
		struct
		{
			bool DrawGray;
		} ConVar;
		struct
		{
			bool ShowChams1;
			bool ShowChams2;
			bool ShowChams3;
			bool ShowChams4;
			bool ShowChams5;
			bool ShowChams6;
			bool ShowChams7;

		} VisualsColors;
		struct
		{
			bool    Enabled;
			bool    EnemyOnly;
			bool    D3D;
			int     Mode;
			bool    Box;
			int    Health;
			bool    Name;
			bool	Hitmarker;
			bool    Weapon;
			bool    Bone;
			bool    Barrel;
			bool    AimPoint;
			bool	RecoilCrosshair;
			bool	SniperCrosshair;
			bool	AutoAccept;
			bool	Glow;
			int     IsVisible;
			int		FOV;
			int     FOV2;
			bool    ThirdPerson;
			bool	ChromeModels;
			bool    bVisibleOnly;
			float	VisibleColor[3];
			float	NonVisibleColor[3];
			//float 	TeamColor[3];
			//float 	TeamColorWall[3];
			//float  	EnemyColor[3];
			//float 	EnemyColorWall[3];
			bool DLight;
			bool NadeTracer;
			bool Callout;
			bool RankESP;
			bool DrawBomb;
			bool DrawDefuser;
			bool DrawGlow;
			int DLightRadius;
			bool BombTimer;
			bool Flashed;
			bool NoName;
			bool InfamyName;
			bool Watermark;
			bool World;
			int DrawGlowS;
			bool Distance;
			bool DrawSnapLines;
			bool SoundESP;
			bool DamageIndicator;
			bool DrawGrenadesGlow;
			bool DrawWeaponsGlow;
			bool Ammo;
			bool ESPTest;
			bool ESPWorldTest;
			bool ESPRunTest;
		}ESP;
	}Visuals;
	struct
	{
		struct
		{
			bool Enabled;
			bool TriggerFriends;
			bool HitChance;
			int Filter;
			int Key;
			int Delay;
			float HitChanceAmount;
			bool Overshoot;
		}Trigger;

		struct
		{
			bool Enabled;
			float Fov;
			int Bone;
			float Smooth[2];
			float Smoothing;
			float lSmooth;
			bool SilentAim;
			bool PerfectSilentAim;
			bool RCS;
			bool rRCS;
			bool pRCS;
			bool WeaponConfigs;
			int LFOV;
			int AimSpeed;
			int MultiplySpeed;
			int FOVBOOST;
			float RCSMin;
			float RCSMax;
			float AngleValue;
			bool RandomizeAngles;
			int LKey;
			bool StandaloneRCS;
			bool EnemyOnly;
			bool VisibleOnly;
			bool DynamicHBox;
			bool DHBoxHead;
			bool DHBoxBody;
			bool DHBoxLowerBody;
			float RCSAmount;
			struct
			{
				int Point;
				bool Head;
				bool Neck;
				bool LowerNeck;
				bool Pelvis;
				bool Body;
				bool Thorax;
				bool Chest;
				bool UpperChest;
				bool RightThigh;
				bool LeftThigh;
				bool RightCalf;
				bool LeftCalf;
				bool RightFoot;
				bool LeftFoot;
				bool RightHand;
				bool LeftHand;
				bool RightUpperArm;
				bool RightForeArm;
				bool LeftUpperArm;
				bool LeftForeArm;
				bool Max;
			}Hitscan;
			struct
			{
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Pistols;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Rifles;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Snipers;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Shotguns;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Machineguns;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}SMGs;
			}Configs;
			float Human = 1;
			float HumanSpeed = 6;
			bool PFOV;
		}Aimbot;
	}Legit;
	struct
	{
		struct
		{
			float MinDamage;
			int AutowallType;
		}AutoWall;
		struct
		{
			// Begin new menu structure



			bool Enabled;
			int Hitbox;
			int Targeting;
			bool AimSmart;
			int iSmartShots;
			int HitScans;
			bool AutoShoot;
			bool AutoScope;
			bool AS1tap;
			bool bHitchanceSnipers;
			int CHitscans;
			bool bHitchance;
			int StopType;
			float Hitchance;
			bool EnemyOnly;
			bool PsuedoSpread;
			bool AntiAntiAim;
			bool SilentAim;
			bool Autowall;
			struct
			{
				int ResolverType;
				QAngle oAngle[64];
				QAngle CAngle[64];
				bool Enemyonly;
				int bone[64];
				int Lisp[64];
				bool bDisableHead[64];
			}AAA;
			struct
			{
				int Point;
				bool Head;
				bool Neck;
				bool LowerNeck;
				bool Pelvis;
				bool Body;
				bool Thorax;
				bool Chest;
				bool UpperChest;
				bool RightThigh;
				bool LeftThigh;
				bool RightCalf;
				bool LeftCalf;
				bool RightFoot;
				bool LeftFoot;
				bool RightHand;
				bool LeftHand;
				bool RightUpperArm;
				bool RightForeArm;
				bool LeftUpperArm;
				bool LeftForeArm;
				bool Max;
			}Hitscan;

			bool AimStep;
			bool AimStepInProgress;
		}Aimbot;
		struct
		{
			bool Enabled;
			int Yaw;
			int Pitch;
			float SpinAmt;
		}AntiAim;
	}Rage;
	struct
	{
		struct
		{
			bool Enabled;
			int Send;
			int Choke;
		}FakeLag;
		struct
		{
			int Key;
			bool Enabled;
		}AirStuck;
		struct
		{
			bool Enabled;
		}bhop;
		struct
		{
			bool Enabled;
			bool REnabled;
			bool Silent;
		}AutoStrafe;
		struct
		{
			bool Enabled;
		}AutoPistol;
		struct
		{
			int Enabled;
			char* buf;
			std::string buff;
		}ClanTags;
		struct
		{
			bool Enabled;
			char buf[64];
		}KillMsg;
		struct
		{
			bool Enabled;
		}Teleport;
		int PanicKey;
		int Flash;
	}PlayerMods;
	struct
	{
		bool Opened = false;
		bool Configs;
		bool test;
		bool Ragebot;
		bool Legitbot;
		bool Visuals;
		bool PlayerMods;
		bool Removals;
		bool Trigger;
		bool VisualColors;
		bool SkinChanger;
		bool WeaponConfigs;
		bool AAC;
		bool Skins;
		bool Console;
		bool PlayerList;
		struct
		{
			bool MoreInfo;
		}pList;
		bool HitScans;
		bool StyleEditor;
		bool SpecList;
		bool active = false;

		//  PlayerList Comboboxes
		bool AntiAimbotCombo;
		bool BoneSelectionCombo;
		bool AntiPitchCombo;
		bool ConfigCombo;
		bool AntiYawCombo;
		bool HitscanTypeCombo;
		bool TargetTypeCombo;
		bool RageHitboxCombo;
		bool StopTypeCombo;
		bool TriggerFilterCombo;
		bool LeagueHitboxCombo;
		bool ShouldDraw;
	}Menu;
	struct
	{
		bool MM = true;
		bool SMAC;
		bool CEVO;
		bool VAC = true;
		bool League = true;
	}AntiCheat;
	struct
	{
		bool Enabled;
		bool NEnabled;
		bool LeftHandKnife;
		int deagle;
		int cz75;
		int p2000;
		int elites;
		int p250;
		int fiveseven;
		int tec9;
		int glock;
		int aug;
		int galil;
		int usps;
		int ak47;
		int famas;
		int m4a4;
		int m4a1s;
		int bizon;
		int mac10;
		int mp7;
		int mp9;
		int p90;
		int m249;
		int ump45;
		int negev;
		int mag7;
		int nova;
		int sawedoff;
		int xm1014;
		int scar20;
		int awp;
		int ssg08;
		int g3sg1;
		int magnum;
		int sg556;
		int KnifeIDb;
		int KnifeIDf;
		int KnifeIDd;
		int KnifeIDg;
		int KnifeIDm;
		int KnifeIDk;
		int KnifeIDh;
		int KnifeIDbutter;
		int KnifeIDfal;
		int KnifeIDdag;
		int KnifeIDbow;
		char buf[64];
		int StatTrak;
		int KnifeSelect;
		struct
		{
			bool Custom0;
			bool Custom1;
			bool Custom2;
			bool Custom3;
			float color0[3];
			float color1[3];
			float color2[3];
			float color3[3];

		}Color;
	}Skins;
	struct
	{
		int Current;
	}Config;
	struct
	{
		bool Uninject;
	}Cheat;
	struct
	{
		bool Enabled;
		char Message[255] = "";
	}IRC;
};
extern cOptions Options;