#pragma once

enum class GameMode : INT32
{
	eBase,
	eCampaign,
	eUnknown2,
	eMultiplayer,
	eUnknown4,
	eSurvival,

	kCount,
};

enum class Difficulty : INT32
{
	eEasy,
	eNormal,
	eHard,
	eImpossible,

	kCount,
};

enum class MapID : INT32
{
	eUndefined = -1,

	eM05 = 178,
	eM10,
	eM20,
	eM30,
	eM35,
	eM45,
	eM50,
	eM52,
	eM60,
	eM70,
	eM70_A,
	eM70_Bonus,

	ePanopticon,
	eBoneyard,
	eLaunchStation,
	eSettlement,
	eIvoryTower,
	eIsland,
	eSwordSlayer,
	eAftship,

	eDLC_Slayer,
	eDLC_Invasion,
	eDLC_Medium,

	eCondemned,
	eTrainingPreserve,

	eCEX_BeaverCreek,
	eCEX_Damnation,
	eCEX_Timberland,
	eCEX_Prisoner,
	eCEX_HangEmHigh,
	eCEX_Headlong,

	eForge_Halo,

	eFF_Park,
	eFF_Corvette,
	eFF_Courtyard,
	eFF_Icecave,
	eFF_Holdout,
	eFF_Ruins,
	eFF_Prototype,
	eFF_Waterfront,
	eFF_Unearthed,

	eCEX_FF_Halo,

	kCount,
};

LPCSTR MapNameFromMapID(MapID mapID)
{
	switch (mapID)
	{
	case MapID::eM05:
		return "m05";
	case MapID::eM10:
		return "m10";
	case MapID::eM20:
		return "m20";
	case MapID::eM30:
		return "m30";
	case MapID::eM35:
		return "m35";
	case MapID::eM45:
		return "m45";
	case MapID::eM50:
		return "m50";
	case MapID::eM52:
		return "m52";
	case MapID::eM60:
		return "m60";
	case MapID::eM70:
		return "m70";
	case MapID::eM70_A:
		return "m70_a";
	case MapID::eM70_Bonus:
		return "m70_bonus";
	case MapID::ePanopticon:
		return "50_panopticon";
	case MapID::eBoneyard:
		return "70_boneyard";
	case MapID::eLaunchStation:
		return "45_launch_station";
	case MapID::eSettlement:
		return "30_settlement";
	case MapID::eIvoryTower:
		return "52_ivory_tower";
	case MapID::eIsland:
		return "35_island";
	case MapID::eSwordSlayer:
		return "20_sword_slayer";
	case MapID::eAftship:
		return "45_aftship";
	case MapID::eDLC_Slayer:
		return "dlc_slayer";
	case MapID::eDLC_Invasion:
		return "dlc_invasion";
	case MapID::eDLC_Medium:
		return "dlc_medium";
	case MapID::eCondemned:
		return "condemned";
	case MapID::eTrainingPreserve:
		return "trainingpreserve";
	case MapID::eCEX_BeaverCreek:
		return "cex_beaver_creek";
	case MapID::eCEX_Damnation:
		return "cex_damnation";
	case MapID::eCEX_Timberland:
		return "cex_timberland";
	case MapID::eCEX_Prisoner:
		return "cex_prisoner";
	case MapID::eCEX_HangEmHigh:
		return "cex_hangemhigh";
	case MapID::eCEX_Headlong:
		return "cex_headlong";
	case MapID::eForge_Halo:
		return "forge_halo";
	case MapID::eFF_Park:
		return "ff50_park";
	case MapID::eFF_Corvette:
		return "ff45_corvette";
	case MapID::eFF_Courtyard:
		return "ff20_courtyard";
	case MapID::eFF_Icecave:
		return "ff60_icecave";
	case MapID::eFF_Holdout:
		return "ff70_holdout";
	case MapID::eFF_Ruins:
		return "ff60_ruins";
	case MapID::eFF_Prototype:
		return "ff10_prototype";
	case MapID::eFF_Waterfront:
		return "ff30_waterfront";
	case MapID::eFF_Unearthed:
		return "ff_unearthed";
	case MapID::eCEX_FF_Halo:
		return "cex_ff_halo";
	}
	return nullptr;
}

INT32 MapNameToMapID(LPCSTR pName)
{
	for (INT32 i = static_cast<INT32>(MapID::eM05); i < static_cast<INT32>(MapID::kCount); i++)
	{
		MapID mapID = static_cast<MapID>(i);
		LPCSTR mapIDStr = MapNameFromMapID(mapID);

		if (mapIDStr != nullptr && (strcmp(pName, mapIDStr) == 0))
		{
			return i;
		}
	}
	return static_cast<INT32>(MapID::eUndefined);
}

class IGameContext
{
public:
	IGameContext();
	~IGameContext();

	IGameContext(IDataAccess *pDataAccess, LPCSTR pEngine, LPCSTR pGame, LPCSTR pMap, LPCSTR pFilm, char windowText[1024]);

	IGameContext *Get();

	void SetGameMode(GameMode gameMode)
	{
		m_gameMode = gameMode;
	}
	void SetGameVariant(IGameVariant *pVariant)
	{
		memcpy(m_gameVariant, pVariant->GetData(), pVariant->GetDataSize());
	}
	void SetMapVariant(IMapVariant *pVariant)
	{
		memcpy(m_mapVariant, pVariant->GetData(), pVariant->GetDataSize());
	}
	void SetMapID(INT32 mapID)
	{
		m_mapID = static_cast<MapID>(mapID);
	}
	void SetSavedFilmPath(LPCSTR pSavedFilmPath)
	{
		m_pSavedFilmPath = pSavedFilmPath;
	}

private:
	GameMode   m_gameMode               = GameMode::eBase;
	char       m_gameVariant[117760]    = {};
	char       m_mapVariant[59392]      = {};
	MapID      m_mapID                  = MapID::eUndefined;
	Difficulty m_difficulty             = Difficulty::eNormal;
	UINT16     m_mapInsertionPoint      = 0;
	UINT8      padding0[10]             = {};
	UINT64     m_active_skull_flags     = 0x0;
	UINT8      padding1[8]              = {};
	LPVOID     m_pGameStateHeader       = nullptr;
	size_t     m_gameStateHeaderSize    = 0;
	LPCSTR     m_pSavedFilmPath         = nullptr;
	INT64      m_sessionPartyID         = 0;
	INT64      m_sessionLocalID         = 0;
	bool       m_sessionIsHost          = true;
	UINT8      m_sessionPadding0[7]     = {};
	INT64      m_sessionPeers[17]       = {};
	size_t     m_sessionPeerCount       = 1;
	char       m_sessionPlayers[16][32] = {};
	size_t     m_sessionPlayerCount     = 1;
	INT64      m_sessionHostID          = 0;
	bool       m_unknown0               = 0;
	UINT8      padding2                 = {};
	bool       m_useCustomEngineName    = 0;
	UINT8      padding3[5]              = {};
	wchar_t   *m_customEngineName       = 0;
};

IGameContext::IGameContext()
{
}

IGameContext::~IGameContext()
{
}

IGameContext::IGameContext(IDataAccess *pDataAccess, LPCSTR pEngine, LPCSTR pGame, LPCSTR pMap, LPCSTR pFilm, char windowText[1024])
{
	IGameVariant *pGameVariant = {};
	IMapVariant *pMapVariant = {};
	ISaveFilmMetadata *pSaveFilmMetadata = {};

	if (pFilm == "")
	{
		if (pGameVariant = pDataAccess->GetGameVariant(pEngine, pGame), pGameVariant)
		{
			printf("%S - %S\n\n", pGameVariant->GetName(), pGameVariant->GetDescription());
		}

		if (pMapVariant = pDataAccess->GetMapVariant(pEngine, pMap), pMapVariant)
		{
			printf("%S - %S\n\n", pMapVariant->GetName(), pMapVariant->GetDescription());
		}
		else
		{
			pMapVariant = pDataAccess->MapVariantCreateFromMapID(MapNameToMapID(pMap));
		}

		if (pGameVariant && pMapVariant)
		{
			LPCSTR pGameVariantName = ""; LPCSTR pMapVariantName = "";
			if (pGameVariant->GetName()[0])
			{
				pGameVariantName = pathf("%S", pGameVariant->GetName());
			}
			else
			{
				pGameVariantName = pGame;
			}

			if (pMapVariant->GetName()[0])
			{
				pMapVariantName = pathf("%S", pGameVariant->GetName());
			}
			else
			{
				pMapVariantName = pMap;
			}

			std::time_t ct = std::time(0);
			sprintf(windowText, "%s on %s, %s", pGameVariantName, pMapVariantName, ctime(&ct));
		}
	}
	else
	{
		if (pSaveFilmMetadata = pDataAccess->GetSaveFilmMetadata(pEngine, pFilm), pSaveFilmMetadata)
		{
			printf("%S - %S\n\n", pSaveFilmMetadata->GetName(), pSaveFilmMetadata->GetDescription());
			sprintf(windowText, "%S", pSaveFilmMetadata->GetDescription());
		}
	}

	if (pFilm && pFilm[0])
	{
		SetSavedFilmPath(pFilm);
	}
	else
	{
		if (pGameVariant)
		{
			GameMode gameMode = GameMode::eBase;
			switch (*reinterpret_cast<INT32 *>(pGameVariant->GetData()))
			{
			case 1:
				gameMode = GameMode::eMultiplayer;
				break;
			case 2:
				gameMode = GameMode::eMultiplayer;
				break;
			case 3:
				gameMode = GameMode::eCampaign;
				break;
			case 4:
				gameMode = GameMode::eSurvival;
				break;
			}
			SetGameVariant(pGameVariant);
			SetGameMode(gameMode);
		}

		if (pMapVariant)
		{
			SetMapVariant(pMapVariant);
			SetMapID(pMapVariant->GetID());
		}
	}

	m_sessionIsHost = true;
	m_sessionPeerCount = 1;
	m_sessionPlayerCount = 1;
}
