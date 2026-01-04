/**
 * @file ESP01_Types.hpp
 * @brief Type definitions, enums, and constants for ESP-01 WiFi module
 * @author Milan
 * @date 2025-12-27
 */

#ifndef ESP01_TYPES_HPP
#define ESP01_TYPES_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* **************************************************
 *                   CONSTANTS                      *
 *************************************************  */

#define ESP01_MAX_RESPONSE_SIZE     256
#define ESP01_MAX_SSID_LENGTH       32
#define ESP01_MAX_PASSWORD_LENGTH   64
#define ESP01_MAX_HOSTNAME_LENGTH   64
#define ESP01_COMMAND_TIMEOUT_MS    5000
#define ESP01_CONNECT_TIMEOUT_MS    15000

/* **************************************************
 *                   ENUMERATIONS                   *
 *************************************************  */

/**
 * @brief ESP-01 module status codes
 */
typedef enum {
    ESP01_OK = 0,
    ESP01_ERROR,
    ESP01_TIMEOUT,
    ESP01_BUSY,
    ESP01_NOT_CONNECTED,
    ESP01_INVALID_PARAM,
    ESP01_BUFFER_OVERFLOW,
    ESP01_PARSE_ERROR
} ESP01_Status_t;

/**
 * @brief WiFi operation modes
 */
typedef enum {
    ESP01_MODE_STATION = 1,      // Connect to access point
    ESP01_MODE_AP = 2,           // Act as access point
    ESP01_MODE_BOTH = 3          // Station + AP
} ESP01_WiFiMode_t;

/**
 * @brief Connection status
 */
typedef enum {
    ESP01_CONN_IDLE = 0,
    ESP01_CONN_CONNECTING,
    ESP01_CONN_CONNECTED,
    ESP01_CONN_DISCONNECTED,
    ESP01_CONN_ERROR
} ESP01_ConnectionStatus_t;

/**
 * @brief TCP/UDP connection type
 */
typedef enum {
    ESP01_CONN_TYPE_TCP = 0,
    ESP01_CONN_TYPE_UDP
} ESP01_ConnectionType_t;

/**
 * @brief AT command state machine states
 */
typedef enum {
    ESP01_STATE_IDLE = 0,
    ESP01_STATE_SENDING_CMD,
    ESP01_STATE_WAITING_RESPONSE,
    ESP01_STATE_RECEIVING_DATA,
    ESP01_STATE_COMPLETE,
    ESP01_STATE_ERROR
} ESP01_State_t;

/* **************************************************
 *                   STRUCTURES                     *
 *************************************************  */

/**
 * @brief WiFi network information
 */
typedef struct {
    char ssid[ESP01_MAX_SSID_LENGTH];
    char password[ESP01_MAX_PASSWORD_LENGTH];
    int8_t rssi;                    // Signal strength
    uint8_t channel;                // WiFi channel
} ESP01_WiFiConfig_t;

/**
 * @brief TCP/IP connection information
 */
typedef struct {
    ESP01_ConnectionType_t type;
    char hostname[ESP01_MAX_HOSTNAME_LENGTH];
    uint16_t port;
    bool isConnected;
    uint8_t linkId;                 // Connection ID (0-4 for multiple connections)
} ESP01_Connection_t;

/**
 * @brief IP configuration
 */
typedef struct {
    uint8_t ip[4];
    uint8_t gateway[4];
    uint8_t netmask[4];
} ESP01_IPConfig_t;

/**
 * @brief Response buffer structure
 */
typedef struct {
    char data[ESP01_MAX_RESPONSE_SIZE];
    uint16_t length;
    bool complete;
} ESP01_Response_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP01_TYPES_HPP */
