#ifndef ANILIST8266_H
#define ANILIST8266_H

#include <Arduino.h>

/* JSON support */
#include <ArduinoJson.h>

/* WiFi and HTTPS requests */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // create TLS connection

/* std includes */
#include <stdarg.h> // variable length args

/* Configuration and secrets */
#include "anilist8266_config.h"

#define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define RESPBUFF_SIZE 2048
const char *_ANILIST_HOST = "https://graphql.anilist.co";

typedef struct graphqlQuery{
    char req[REQBUFF_SIZE];
    int status;
    char resp[RESPBUFF_SIZE];
} GraphqlQuery;


typedef struct anilistUser{
    long userId;
    char username[128];
    int episodesWatched;
    int minutesWatched;    
} AnilistUser;


/* main */
void initSerial();
void initWifi();

GraphqlQuery *anilistRequest(WiFiClientSecure client, const char *query);
AnilistUser *createUser(JsonObject data);

#endif