/*
 * Copyright (c) 2020 Sellig Zeittom
 */

#ifndef _GATT_WRAPPER_H__
#define _GATT_WRAPPER_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <zephyr.h>
#include <zephyr/types.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/printk.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/gatt_dm.h>


/*
 * Get GATT subscribe parameters
 */ 
int gatt_get_subscribe_parameters(struct bt_gatt_dm *discovery, struct bt_uuid* uuid, bt_gatt_notify_func_t func, struct bt_gatt_subscribe_params* parameters);

/*
 * Get GATT read parameters
 */ 
int gatt_get_subscribe_parameters(struct bt_gatt_dm *discovery, struct bt_uuid* uuid, bt_gatt_read_func_t func, struct bt_gatt_read_params* parameters);

/*
 * Discover a service
 */ 
int gatt_discover_services(struct bt_conn *connection, struct bt_uuid* uuid, const struct bt_gatt_dm_cb *callback);

/*
 * Subscribe to notifications on a characteristic
 */ 
int gatt_subscribe_to_notifications(struct bt_conn *connection, struct bt_gatt_subscribe_params* params);

/*
 * Read the value of a characteristic
 */ 
int gatt_read_characteristic(struct bt_conn *connection, struct bt_gatt_read_params* read_params);

#ifdef __cplusplus
}
#endif

#endif /* _GATT_WRAPPER_H__ */
