//
// Created by PinkySmile on 02/12/2020.
//

#include "SokuAddresses.hpp"
#include "BattleManager.hpp"
#include "SokuFct.hpp"

namespace SokuLib
{
	void (__thiscall CharacterManager::* const CharacterManager_PlaySE)(int id) = union_cast<void (CharacterManager::*)(int)>(ADDR_PLAY_SE_CHARACTER);

	BattleManager &getBattleMgr()
	{
		return **reinterpret_cast<BattleManager **>(ADDR_BATTLE_MANAGER);
	}

	void (__cdecl * const setBattleMode)(int comm, int sub) = reinterpret_cast<void (__cdecl *)(int, int)>(ADDR_SET_BATTLE_MODE);
	String &player1Profile = *reinterpret_cast<String *>(ADDR_PLAYER1_PROFILE_STR);
	String &player2Profile = *reinterpret_cast<String *>(ADDR_PLAYER2_PROFILE_STR);
}