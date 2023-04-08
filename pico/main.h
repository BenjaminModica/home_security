#ifndef PICO_TCP_MULTICORE_SERVER_H
#define PICO_TCP_MULTICORE_SERVER_H

#include <string.h>
#include <stdlib.h>

#include "secrets.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "boards/pico_w.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "mfrc522.h"

#define TCP_PORT 4242
#define DEBUG_printf printf
#define BUF_SIZE_RECV 1
#define BUF_SIZE_SENT 24
#define TEST_ITERATIONS 10
#define POLL_TIME_S 60

#define LED_PIN_GREEN 28
#define LED_PIN_RED 27
#define LED_PIN_YELLOW 22
#define PIEZO_PIN 14
#define PIR_PIN 26

#define DEACTIVATED_STATE 1
#define ACTIVATED_STATE 2
#define TRIPPED_STATE 3
#define ALARM_STATE 4

static uint8_t state;
static uint8_t auth_counter;

typedef struct TCP_SERVER_T_ {
    struct tcp_pcb *server_pcb;
    struct tcp_pcb *client_pcb;
    uint8_t buffer_sent[BUF_SIZE_SENT];
    uint8_t buffer_recv[BUF_SIZE_RECV];
    int sent_len;
    int recv_len;
    int run_count;
} TCP_SERVER_T;

struct repeating_timer timer_slow;
struct repeating_timer timer_fast;
struct repeating_timer timer_counter;

bool repeating_timer_callback(struct repeating_timer *t);
bool repeating_timer_callback_counter(struct repeating_timer *t);

static TCP_SERVER_T* tcp_server_init(void);

static err_t tcp_client_close(void *arg);

static err_t tcp_server_result(void *arg, int status);

static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);

err_t tcp_server_send_data(void *arg, struct tcp_pcb *tpcb);

err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);

static void tcp_server_err(void *arg, err_t err);

static err_t tcp_server_accept(void *arg, struct tcp_pcb *client_pcb, err_t err);

static bool tcp_server_open(void *arg);

void run_tcp_server(void);

uint8_t wifi_init();

#endif