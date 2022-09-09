//
// Created by DPhoenix on 12/06/2022.
//

#ifndef SOKULIB_GAMEOBJECT_HPP
#define SOKULIB_GAMEOBJECT_HPP

#include "AnimationObject.hpp"
#include "Character.hpp"
#include "Deque.hpp"

namespace SokuLib {
namespace v2 {
	class GameObject : public AnimationObject {
	public:
		// offset 0x158
		struct GameInfo {
			CharacterFrameData* frameData;
			CharacterSequenceData* sequenceData;
			Map<int, CharacterSequenceData*>* patternMap;
			void* soundTable;
			void* owner = 0;
			void* ally = 0;
			void* opponent = 0;
			int unknown174 = 0;
		} gameData;
		List<void*> unknown178;

		// offset 0x184 (hp and state)
		short unknown184;
		short unknown186;
		int unknown188 = 0;
		char unknown18c = 0xff;
		char unknown18d[3]; // align 0x3?
		int unknown190 = 0;
		char unknown194 = 0;
		char unknown195; // align 0x1?
		short unknown196 = 0;
		char unknown198[0x8];
		char unknown1a0 = 0;
		char unknown1a1 = 0;
		char unknown1a2[2]; // align 0x2?
		char unknown1a4[8];
		char unknown1ac = 1;
		char unknown1ad[3]; // align 0x3?
		int unknown1b0 = 0;
		char unknown1b4[0xC];

		// offset 0x1c0
		struct BoxInfo {
			CharacterFrameData* unknown1c0 = 0;
			CharacterSequenceData* unknown1c4;
			Action unknown1c8;
			char unknown1ca; // collisionBoxCount?
			char hitBoxCount = 0;
			char hurtBoxCount = 0;
			// align 0x3

			// offset 0x1d0
			Box hurtBoxes[5];
			Box hitBoxes[5];

			// offset 0x270
			RotationBox rotationBuffer[10];
			char unknown310[0x10]; // collisionBox?

			// offset 0x320
			RotationBox* hitBoxesRotation[5] = {0};
			RotationBox* hurtBoxesRotation[5] = {0};
			Box* collisionBoxPtr = 0;
		} boxData;
	};

	class CharacterObject : public GameObject {
	public:
		int unknown34C = 1;
		int unknown350 = 0;
		int unknown354 = 0;
		char unknown358[4];
		int unknown35C = 0;
		short unknown360 = 0;
		short unknown362 = 0;

		// offset 0x364
		char unknown364[0x38]; // 0x364 and 0x398 = owner
		int unknown39C = 0;
		List<int> unknown3A0;

		inline CharacterObject() { unknown184 = unknown186 = 0; }
	};

	class Character : public GameObject {
	public:
		int characterIndex;
		bool isRight;
		char palette;
		char unknown352[0x2]; // align 0x2?
		int unknownTexId354 = 0;
		Sprite unknown358; // sizeof = 0x94
		int unknownTexId3EC = 0;
		Sprite unknown3F0; // sizeof = 0x94
		char unknown484[0x14];
		char unknown498[0xe4]; // playing status

		//offset 0x57c (some class)
		struct DeckInfo {
			Deque<int> unknown57C; // maybe are floats
			struct UnknownData60 { char unknown[0x60]; };
			Map<int, UnknownData60> unknown590;
			Deque<unsigned short> unknown59C;
			Deque<unsigned short> unknown5B0;
			char unknown0x5C4[0x20];

			// offset 0x5e4
			short cardGauge;
			unsigned char cardCount;
			unsigned char cardSlots;

			struct Card {
				unsigned short id;
				unsigned short cost;
				Sprite sprite;
			};
			Deque<Card> cardQueue;
			Deque<short> usedCards;
		} deckData; //??

		// offset 0x610
		Sprite unknown610;
		char unknown6A4[0x54]; // skillLevels?
		void* objectList; // TODO = new ObjectManager
		Deque<CharacterSequenceData> patternData;
		char unknown710[4];

		struct {
			struct UnknownData { int unknown; SpriteEx sprite; }; // unsure
			List<UnknownData> unknown714;
			char unknown720 = 5;
			char unknown721;
			short unknown722 = 15;
			char unknown724[0x8];
			Deque<int> unknown72C; // seems to hold textureIDs
			char unknown740[0x10];
		} unknown714;

		// offset 0x750
		KeyManager* keyManager;
		KeyInput keyInput;
		char unknown774[0x3C];
		Deque<char> unknown7B0; // unsure of the type
		char unknown7C4[8];
		//KeyCombination keyCombination;
		char unknown7CC;
		// align 0x3

		// unsure of the size here and beyond

		inline Character(const PlayerInfo& playerInfo) : keyManager(playerInfo.keyManager) {
			gameData.owner = gameData.ally = this;

			gameData.patternMap = SokuLib::New<Map<int, CharacterSequenceData*>>(1,*(Map<int, CharacterSequenceData*>*)0x89aae8);
			textures = SokuLib::New<Vector<int>>(1,*(Vector<int>*)0x89aac4);
			gameData.soundTable = SokuLib::New<int>(400);
			memset(gameData.soundTable, 0, 400);

			characterIndex = playerInfo.character;
			isRight = playerInfo.isRight;
			palette = playerInfo.palette;
			deckData.unknown59C = playerInfo.effectiveDeck;
			deckData.unknown5B0 = playerInfo.effectiveDeck;
			if (playerInfo.keyManager) unknown7CC = playerInfo.padding2;
			else unknown7CC = 0;
		}
	};

	class CharacterCirno : public Character {
	public:
		// vtable: 0x85eab4
		char unknown[0x1C0];

		virtual void setActionSequence(short a, short b) { (this->*union_cast<void(CharacterCirno::*)(short, short)>(((void**)0x85eab4)[1]))(a, b); }
		virtual void setAction(short a) { (this->*union_cast<void(CharacterCirno::*)(short)>(((void**)0x85eab4)[2]))(a); }
		virtual void setSequence(short a) { (this->*union_cast<void(CharacterCirno::*)(short)>(((void**)0x85eab4)[3]))(a); }
		virtual void resetSequence() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[4]))(); }
		virtual bool nextSequence() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[5]))(); }
		virtual void prevSequence() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[6]))(); }
		virtual void setPose(short a) { (this->*union_cast<void(CharacterCirno::*)(short)>(((void**)0x85eab4)[7]))(a); }
		virtual bool nextPose() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[8]))(); }
		virtual void prevPose() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[9]))(); }
		virtual void update() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[10]))(); }
		virtual void render() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[11]))(); }
		virtual void render2() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[12]))(); }
		virtual void applyTransform() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[13]))(); }
		virtual void onRenderEnd() { (this->*union_cast<void(CharacterCirno::*)()>(((void**)0x85eab4)[14]))(); }

		inline CharacterCirno(const PlayerInfo& playerInfo) : Character(playerInfo) {
			objectList = SokuLib::NewFct(0x68);
			(reinterpret_cast<void(__fastcall*)(void*, int, void*)>(0x6fb5f0))(objectList, 0, this);
		}
	};
}
}

#endif // SOKULIB_GAMEOBJECT_HPP