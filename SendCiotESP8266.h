#ifndef SENDCIOTESP8266_H_
#define SENDCIOTESP8266_H_

#include <Arduino.h>

class SendCiotESP8266{
	public:
		String send(String array[][2], int elements, String apikey, String device);
};

#endif
