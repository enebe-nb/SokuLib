//
// Created by Gegel85 on 04/11/2020.
//

#ifndef SOKULIB_SOUNDMANAGER_HPP
#define SOKULIB_SOUNDMANAGER_HPP


#include <Windows.h>

namespace SokuLib
{
	// SE�Đ�
	extern void (* const playSEWaveBuffer)(int id);
	extern void (* const playNetBell)(int id);
	void playSECharacter(DWORD charAddr, int id);
}



#endif //SOKULIB_SOUNDMANAGER_HPP
