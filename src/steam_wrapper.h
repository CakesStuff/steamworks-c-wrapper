/*
 * Copyright (c) 2015 CIPRIAN ILIES
 * See LICENSE for details.
 */

#ifndef STEAM_WRAPPER_H
#define STEAM_WRAPPER_H

#include <stdint.h>

bool c_SteamAPI_Init();

void c_SteamAPI_Shutdown();

bool c_SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID);

bool c_SteamUser_BLoggedOn();

typedef enum c_EServerMode_t
{
	c_eServerModeInvalid = 0,
	c_eServerModeNoAuthentication = 1,
	c_eServerModeAuthentication = 2,
	c_eServerModeAuthenticationAndSecure = 3,
} c_EServerMode;

bool c_SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, c_EServerMode eServerMode, const char* pchVersionString);

void c_SteamGameServer_Shutdown();

/*
 * Note: The Steam API prototype looks like this: S_API ISteamGameServer* SteamGameServer().
 * This returns a void pointer to the return value of that function.
 * At this point in time, there isn't really much value in the return data except to check if it's NULL or something else,
 * seeing as the data being pointed to is a class.
 * What the intended purpose of the return data is, I don't know.
 */
void* c_SteamGameServer();

/*
 * Would it be better to create a struct with function pointers to all of these functions?
 */
void c_SteamGameServer_SetModDir(const char *pszModDir);

void c_SteamGameServer_SetProduct(const char *pszProduct);

void c_SteamGameServer_SetGameDescription(const char *pszGameDescription);

void c_SteamGameServer_LogOnAnonymous();

void c_SteamGameServer_EnableHeartbeats(bool bActive);

void c_SteamGameServer_LogOff();

/*
 * Note that the original function takes a CSteamID.
 * steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 * I sure hope this void pointer is sufficient for dealing with CSteamID.
 */
void c_SteamGameServerNetworking_AcceptP2PSessionWithUser(void* steamIDRemote);

typedef enum c_EP2PSend_t
{
	c_k_EP2PSendUnreliable = 0,
	c_k_EP2PSendUnreliableNoDelay = 1,
	c_k_EP2PSendReliable = 2,
	c_k_EP2PSendReliableWithBuffering = 3,
} c_EP2PSend;

/*
 * NOTE: nChannel defaults to zero in the steam API. That does not happen here.
 * Because, you know, C.
 * NOTE 2: steamIDRemote should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
bool c_SteamGameServerNetworking_SendP2PPacket(void* steamIDRemote, const void *pubData, uint32_t cubData, c_EP2PSend eP2PSendType, int nChannel);

typedef enum c_EBeginAuthSessionResult_t
{
	c_k_EBeginAuthSessionResultOK = 0,
	c_k_EBeginAuthSessionResultInvalidTicket = 1,
	c_k_EBeginAuthSessionResultDuplicateRequest = 2,
	c_k_EBeginAuthSessionResultInvalidVersion = 3,
	c_k_EBeginAuthSessionResultGameMismatch = 4,
	c_k_EBeginAuthSessionResultExpiredTicket = 5,
} c_EBeginAuthSessionResult;

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
c_EBeginAuthSessionResult c_SteamGameServer_BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, void* steamID);

/*
 * NOTE: steamID should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void c_SteamGameServer_EndAuthSession(void* steamID);

/*
 * NOTE: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool c_SteamGameServerNetworking_IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel);

/*
 * NOTE: psteamIDRemote should be a CSteamID pointer. It gets converted back to a CSteamID pointer in this function.
 * NOTE 2: nChannel defaults to zero in the steam API. That is not so here because, you know, C.
 */
bool c_SteamGameServerNetworking_ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, void* psteamIDRemote, int nChannel);

uint64_t c_SteamGameServer_GetSteamID_ConvertToUInt64();

bool c_SteamGameServer_BSecure();

/*
 * NOTE: steamIDUser should be a pointer to a CSteamID. It gets converted back to a CSteamID in this function.
 */
void c_SteamGameServer_SendUserDisconnect(void* steamIDUser);

void c_SteamGameServer_RunCallbacks();

void c_SteamGameServer_SetMaxPlayerCount(int cPlayersMax);

void c_SteamGameServer_SetPasswordProtected(bool bPasswordProtected);

void c_SteamGameServer_SetServerName(const char *pszServerName);

void c_SteamGameServer_SetBotPlayerCount(int cBotplayers);

void c_SteamGameServer_SetMapName(const char *pszMapName);

bool c_SteamGameServer_BUpdateUserData(void* steamIDUser, const char *pchPlayerName, uint32_t uScore);

#endif