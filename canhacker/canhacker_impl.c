#include "canhacker_impl.h"
#include "systick.h"

static uint32_t timestamp=0;


uint32_t uiGetTimestamp(void)
{
	uint32_t new_tm = uiGetTimeMs();
	static uint32_t old_tm=0;
	
	timestamp += (new_tm - old_tm);

	if(timestamp >=59999)timestamp=0;
		
	old_tm = new_tm;
	
	return timestamp;
}

uint8_t uiAscii2byte(uint8_t val)
{
    if (val >= 'a') {
        return val - 'a' + 10; // convert chars a-f
    }
    if (val >= 'A') {
        return val - 'A' + 10; // convert chars A-F
    }
    return val - '0';     // convert chars 0-9
}

uint8_t uiNibble2ascii(uint8_t byte)
{
    byte &= 0x0F;
    return byte < 10 ? byte + 48 : byte + 55;
}

void PackDataCANHackerToCAN(int offset, uint8_t dlc,uint8_t *dataforpack,uint32_t *dataispack)
{
	for(int i=0,bnum=offset, j=0; ((i<(dlc/4) + ((dlc%4==0)?0:1)) && ((bnum-offset) < (dlc*2)));i +=((((bnum -offset)%8)==0)?1:0))
	{
		
		dataispack[i] |= (((uiAscii2byte(dataforpack[bnum]))<<4) | ((uiAscii2byte(dataforpack[bnum+1]))))<<(j++*8);
		j &= 3;bnum +=2;
	}		
}

uint8_t uiPackDataCANToCANHacker(int offset, uint8_t dlc,uint32_t *dataforpack,uint8_t *dataispack)
{
	uint8_t bnum=0;
	for(uint8_t i=0,j=0;bnum<dlc*2; j += ((i%8)==0)?1:0,i &=7)
	{
		dataispack[offset+bnum++] = uiNibble2ascii(dataforpack[j]>>((i+1)*4));
		dataispack[offset+bnum++] = uiNibble2ascii(dataforpack[j]>>(i*4));
		i += 2;
	}
	return offset+bnum;
}

