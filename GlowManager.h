#pragma once


class CGlowObjectEntityManager
{
public:
	class GlowObjectEntityDefinition_t
	{
	public:
		void set(Color color)
		{
			m_vGlowColor = Vector(color.rBase(), color.gBase(), color.bBase());
			m_flGlowAlpha = color.aBase();
			m_bRenderWhenOccluded = true;
			m_bRenderWhenUnoccluded = false;
			m_flBloomAmount = 1.f;
		}

		CBaseEntity* getEntity()
		{
			return m_hEntity;
		}

		bool IsEmpty() const { return m_nNextFreeSlot != GlowObjectEntityDefinition_t::ENTRY_IN_USE; }

	public:
		CBaseEntity*		m_hEntity;
		Vector				m_vGlowColor;
		float				m_flGlowAlpha;

		char				unknown[4];
		float				flUnk;
		float				m_flBloomAmount;
		float				localplayeriszeropoint3;


		bool				m_bRenderWhenOccluded;
		bool				m_bRenderWhenUnoccluded;
		bool				m_bFullBloomRender;
		char				unknown1[1];


		int					m_nFullBloomStencilTestValue;
		int					iUnk;
		int					m_nSplitScreenSlot;
		int					m_nNextFreeSlot;

		// Special values for GlowObjectDefinition_t::m_nNextFreeSlot
		static const int END_OF_FREE_LIST = -1;
		static const int ENTRY_IN_USE = -2;
	};

	GlowObjectEntityDefinition_t* m_GlowObjectDefinitions;
	int		max_size;
	int		pad;
	int		size;
	GlowObjectEntityDefinition_t* m_GlowObjectDefinitions2;
	int		currentObjects;
};
typedef CGlowObjectEntityManager*(__thiscall* GlowObjectGrenadePointer_t)();


class CGlowObjectManager
{
public:
	struct GlowObjectDefinition_t
	{
		CBaseEntity*	entity;
		Vector			glowColor;
		float			glowAlpha;
		unsigned char   junk[16];
		bool			shouldGlow;
		bool			isUnknown;
		bool			isFullBloom;
		unsigned char   junk2[14];
	};

	std::vector<GlowObjectDefinition_t> glowObjectDefinitions;
	int firstFreeSlot;
};

typedef CGlowObjectManager*(__thiscall* GlowObjectPointer_t)();