#pragma once

class IDataAccess
{
public:
	virtual void                     Free()                                             = 0;
	virtual class IMapVariant       *MapVariantCreateFromFile(char *, size_t)           = 0;
	virtual class IMapVariant       *MapVariantCreateFromMapID(INT32)                   = 0;
	virtual class IMapVariant       *MapVariantCreateDefault(char *)                    = 0;
	virtual class IGameVariant      *GameVariantCreateFromFile(char *, size_t)          = 0;
	virtual class IGameVariant      *GameVariantCreateDefault(int)                      = 0;
	virtual bool                     LoadMapFromVariants(IGameVariant *, IMapVariant *) = 0;
	virtual class ISaveFilmMetadata *SaveFilmMetadataCreateFromFile(char *, size_t)     = 0;

	class IGameVariant *GetGameVariant(LPCSTR pEngine, LPCSTR pName)
	{
		IFileAccess               *pFile        = {};
		static class IGameVariant *pGameVariant = {};
		size_t                     file_size    = {};

		if (pFile = new IFileAccess(pathf("%s\\game_variants\\%s.bin", pEngine, pName)), pFile->FileOpen())
		{
			pGameVariant = GameVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pFile = new IFileAccess(pathf("%s\\hopper_game_variants\\%s.bin", pEngine, pName)), pFile->FileOpen())
		{
			pGameVariant = GameVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pFile = new IFileAccess(pathf("%s\\AppData\\LocalLow\\MCC\\Temporary\\UserContent\\%s\\GameType\\%s.bin", GetUserprofileVariable(), pEngine, pName)), pFile->FileOpen())
		{
			pGameVariant = GameVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}

		pFile->FileClose();
		return pGameVariant;
	}

	class IMapVariant *GetMapVariant(LPCSTR pEngine, LPCSTR pName)
	{
		IFileAccess              *pFile       = {};
		size_t                    file_size   = {};
		static class IMapVariant *pMapVariant = {};

		if (pFile = new IFileAccess(pathf("%s\\map_variants\\%s.mvar", pEngine, pName)), pFile->FileOpen())
		{
			pMapVariant = MapVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pFile = new IFileAccess(pathf("%s\\hopper_map_variants\\%s.mvar", pEngine, pName)), pFile->FileOpen())
		{
			pMapVariant = MapVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pFile = new IFileAccess(pathf("%s\\AppData\\LocalLow\\MCC\\Temporary\\UserContent\\%s\\Map\\%s.bin", GetUserprofileVariable(), pEngine, pName)), pFile->FileOpen())
		{
			pMapVariant = MapVariantCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}

		pFile->FileClose();
		return pMapVariant;
	}

	class ISaveFilmMetadata *GetSaveFilmMetadata(LPCSTR pEngine, LPCSTR &rpName)
	{
		static LPCSTR                   pPath             = {};
		IFileAccess                    *pFile             = {};
		size_t                          file_size         = {};
		static class ISaveFilmMetadata *pSaveFilmMetadata = {};

		if (pPath = pathf("%s\\Temporary\\autosave\\%s.film", pEngine, rpName), pFile = new IFileAccess(pPath), pFile->FileOpen())
		{
			pSaveFilmMetadata = SaveFilmMetadataCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pPath = pathf("%s\\AppData\\LocalLow\\MCC\\Temporary\\%s\\autosave\\%s.film", GetUserprofileVariable(), pEngine, rpName), pFile = new IFileAccess(pPath), pFile->FileOpen())
		{
			pSaveFilmMetadata = SaveFilmMetadataCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		else if (pPath = pathf("%s\\AppData\\LocalLow\\MCC\\Temporary\\UserContent\\%s\\Movie\\%s.mov", GetUserprofileVariable(), pEngine, rpName), pFile = new IFileAccess(pPath), pFile->FileOpen())
		{
			pSaveFilmMetadata = SaveFilmMetadataCreateFromFile(pFile->GetBuffer(file_size), file_size);
		}
		rpName = pPath;

		pFile->FileClose();
		return pSaveFilmMetadata;
	}

private:
	void *m_HeapAllocation;
	void *m_function0;
	void *m_HeapAllocationSize;
	void *m_function1;
};
