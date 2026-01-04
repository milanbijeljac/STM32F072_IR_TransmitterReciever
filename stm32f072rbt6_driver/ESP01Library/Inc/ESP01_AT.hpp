/**
 * @file ESP01_AT.hpp
 * @brief AT command definitions for ESP-01 WiFi module
 * @author Milan
 * @date 2025-12-27
 */

#ifndef ESP01_AT_HPP
#define ESP01_AT_HPP

/* **************************************************
 *               AT COMMAND STRINGS                 *
 *************************************************  */

// Basic AT commands
#define AT_CMD_TEST             "AT\r\n"
#define AT_CMD_RESET            "AT+RST\r\n"
#define AT_CMD_VERSION          "AT+GMR\r\n"
#define AT_CMD_ECHO_OFF         "ATE0\r\n"
#define AT_CMD_ECHO_ON          "ATE1\r\n"

// WiFi Mode commands
#define AT_CMD_CWMODE_GET       "AT+CWMODE?\r\n"
#define AT_CMD_CWMODE_SET       "AT+CWMODE=%d\r\n"         // 1=Station, 2=AP, 3=Both

// WiFi Connection commands
#define AT_CMD_CWJAP_CONNECT    "AT+CWJAP=\"%s\",\"%s\"\r\n"  // SSID, Password
#define AT_CMD_CWJAP_GET        "AT+CWJAP?\r\n"
#define AT_CMD_CWQAP            "AT+CWQAP\r\n"             // Disconnect from AP

// IP commands
#define AT_CMD_CIFSR            "AT+CIFSR\r\n"             // Get IP address
#define AT_CMD_CIPSTATUS        "AT+CIPSTATUS\r\n"         // Get connection status

// TCP/IP Connection commands
#define AT_CMD_CIPSTART_TCP     "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n"  // Host, Port
#define AT_CMD_CIPSTART_UDP     "AT+CIPSTART=\"UDP\",\"%s\",%d\r\n"  // Host, Port
#define AT_CMD_CIPCLOSE         "AT+CIPCLOSE\r\n"
#define AT_CMD_CIPMUX_SINGLE    "AT+CIPMUX=0\r\n"         // Single connection
#define AT_CMD_CIPMUX_MULTIPLE  "AT+CIPMUX=1\r\n"         // Multiple connections

// Data Transmission commands
#define AT_CMD_CIPSEND          "AT+CIPSEND=%d\r\n"       // Length
#define AT_CMD_CIPMODE_NORMAL   "AT+CIPMODE=0\r\n"        // Normal mode
#define AT_CMD_CIPMODE_TRANSP   "AT+CIPMODE=1\r\n"        // Transparent mode

// Server commands (for AP mode)
#define AT_CMD_CIPSERVER_START  "AT+CIPSERVER=1,%d\r\n"   // Port
#define AT_CMD_CIPSERVER_STOP   "AT+CIPSERVER=0\r\n"
#define AT_CMD_CIPSTO           "AT+CIPSTO=%d\r\n"        // Server timeout (seconds)

/* **************************************************
 *            AT RESPONSE STRINGS                   *
 *************************************************  */

#define AT_RESP_OK              "OK"
#define AT_RESP_ERROR           "ERROR"
#define AT_RESP_FAIL            "FAIL"
#define AT_RESP_READY           "ready"
#define AT_RESP_WIFI_CONNECTED  "WIFI CONNECTED"
#define AT_RESP_WIFI_GOT_IP     "WIFI GOT IP"
#define AT_RESP_WIFI_DISCONNECT "WIFI DISCONNECT"
#define AT_RESP_CONNECT         "CONNECT"
#define AT_RESP_CLOSED          "CLOSED"
#define AT_RESP_SEND_OK         "SEND OK"
#define AT_RESP_SEND_FAIL       "SEND FAIL"

// Data reception indication
#define AT_RESP_IPD_PREFIX      "+IPD,"                   // +IPD,<length>:<data>

/* **************************************************
 *                RESPONSE TIMEOUTS                 *
 *************************************************  */

#define AT_TIMEOUT_SHORT        1000    // ms - for simple commands
#define AT_TIMEOUT_MEDIUM       3000    // ms - for mode changes
#define AT_TIMEOUT_LONG         10000   // ms - for WiFi connection
#define AT_TIMEOUT_VERY_LONG    15000   // ms - for TCP connection

#endif /* ESP01_AT_HPP */
