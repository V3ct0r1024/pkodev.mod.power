#pragma once

namespace pkodev
{
	// 3D vector structure
	struct D3DXVECTOR3
	{
		float x;
		float y;
		float z;
	};

	// Character info from CharacterInfo.txt structure
	struct ChaRecord
	{
		char nop0[0x010C]; // Offset 0
		float height;      // Character height (0x010C)
	};

	// Character structure
	struct Character
	{
		char nop0[0x14];             // Offset 0
		int world_id;                // World ID (0x14)
		char nop1[0xB8];             // Offset 1
		int level;                   // Level (0xD0)
		int hp;                      // HP (0xD4)
		char nop2[0x5c];             // Offset 2
		int unknown0;                // Type ??? (0x0134)
		char nop3[0x14];             // Offset 3
		int max_hp;                  // Max HP (0x014C)
		char nop4[0x02c4];           // Offset 4
		ChaRecord* Info;             // Character info (0x0414)
		char nop5[0x04];             // Offset 5
		const char name[0x21];       // Charater name (0x043D)
		const char human_name[0x21]; // Charater human name ??? (0x041C)
		char nop6[0x86];             // Offset 6 
		int  guild_id;               // Guild ID (0x04E4)
		int  guild_color;            // Guild color (0x04E8)
		int  name_color;             // Name color имени (0x04Ec)
		char shop_name[0x21];        // Set stall name (0x04F0) 
		char pre_name[0x14];         // Title (0x0511) 
		char nop7[0x0003];           // Offset 7 (0x0525)
		int  side_id;                // Side ID (0x0528)
		char nop8[4];                // Offset 8
		void* pStateMgr;             // Effects (0x0530)
		int cha_state;               // State (0x0534)
		char nop9[0x28];             // Offset 9
		int area_type;               // Area type (0x0560)
		char nop10[0x00D0];          // Offset 10 (0x0564)
		short int head_id;           // Head item ID (0x‭0634‬)
		char nop11[0x0012];          // Offset 11 (0x0636)
		short int head_app_id;       // Head apparel item ID (0x‭0648‬)
		char nop12[0x0314];          // Offset 12 (0x064A)
		short int ring_id;           // Ring item ID (0x095E)
		char nop13[0x01E4];          // Offset 13
		short int neck_id;           // Necklace item ID (0x0B44)
		char nop14[0x0156];          // Offset 14
		int  party_id;               // Party ID (0x0C9C)
		char motto[0x29];            // Motto (0x0CA0)
		char nop15[0x00B];           // Offset 15
		int modal_type;              // Modal type ??? (0x0CD4)
		int type;                    // Type (0x0CD8)
		char nop16[0x08];            // Offset 16
		int cha_id;                  // Character ID (0x0CE4)
	};

	// Power structure
	struct Power
	{
		// Character world ID
		unsigned int world_id;

		// Power amount
		unsigned int power;

		// Color (0xFFRRGGBB)
		unsigned int color;


		// Default constructor
		Power() :
			world_id(), power(0), color(0xFFFFFFFF) { }

		// Constructor
		Power(unsigned int world_id_, unsigned int power_, unsigned int color_) :
			world_id(world_id_), power(power_), color(color_) { }
	};
}