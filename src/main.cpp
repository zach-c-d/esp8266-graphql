#include <Arduino.h>

/* JSON support */
#include <ArduinoJson.h>

/* WiFi and HTTPS requests */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection

WiFiClientSecure client;
char queryBuffer[512];

// #define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.chalmersproject.com";

// 
// set this captive portal on esp8266 at startup?
// or set this from esp mac address? or some other locally stored unique identifier?
// scan qr code on back with phone -> opens admin portal on web browser ->
//
const char *_SHELTER_ID = "sl;akfj;pqoelkj,a.jf,mqj."; 
const char *_SHELTER_SECRET = "sl;akfj;pqoelkj,a.jf,mqj.";


void setup()
{
  Serial.begin(115200);
  // sprintf(queryBuffer,
        // "{User(search:\"%s\"){id name statistics{anime{episodesWatched minutesWatched}}}}", _SHELTER_ID);
  sprintf(queryBuffer,
          "{mutation \ 
             { \
                ShelterMeasurementMutations(signal_id: \"%s\", signal_secret: \"%s\")}{id name statistics{anime{episodesWatched minutesWatched}}}}", _SHELTER_ID, _SHELTER_SECRET);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
typedef struct graphqlQuery
{
  char req[REQBUFF_SIZE];
  int status;
  char resp[RESPBUFF_SIZE];
} GraphqlQuery;

typedef struct send_occupancy_update
{
  long userId;
  char username[128];
  int episodesWatched;
  int minutesWatched;
} Send_Occupancy_Update;
Send_Occupancy_Update *update_Occupancy(JsonObject data);

// HTTP POST to Anilist GraphQL API
GraphqlQuery *occupancy_request(WiFiClientSecure client, const char *query)
{
  GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
  HTTPClient http;
  StaticJsonDocument<200> reqJson;
  Serial.println("Sending HTTP POST");
  http.begin(client, _API_HOST);
  http.addHeader("Content-Type", "application/json");
  reqJson["query"] = query;

  serializeJson(reqJson, graphql->req);
  Serial.printf("HTTP REQ: %s\n", graphql->req);
  graphql->status = http.POST(graphql->req);
}