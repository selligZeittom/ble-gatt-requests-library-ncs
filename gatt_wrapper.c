#include "gatt_wrapper.h"

/*
 * Get GATT subscribe parameters
 * 
 * @param discovery: 	pointer to the discovery data received after calling gatt_discover_services(...)
 * @param uuid: 		characteristic's uuid
 * @param func: 		callback function for the notification
 * @param parameters: 	read parameters to be filled, must be statically created
 */ 
int gatt_get_subscribe_parameters(struct bt_gatt_dm *discovery, struct bt_uuid* uuid, bt_gatt_notify_func_t func, struct bt_gatt_subscribe_params* parameters)
{
	// Get the characteristic and descriptors
	const struct bt_gatt_attr* characteristic = bt_gatt_dm_char_by_uuid(discovery, uuid);
	if (!characteristic) {
		printk("Missing characteristic in discovery data.\n");
		return -1;
	}
	const struct bt_gatt_attr* descriptor = bt_gatt_dm_desc_by_uuid(discovery, characteristic, uuid);
	if (!descriptor) {
		printk("Missing descriptor in discovery data.\n");
		return -1;
	}
	const struct bt_gatt_attr* ccc_descriptor = bt_gatt_dm_desc_by_uuid(discovery, characteristic, BT_UUID_GATT_CCC);
	if (!ccc_descriptor) {
		printk("Missing CCC descriptor in discovery data.\n");
		return -1;
	}

	// Set up the subscribe parameters
	parameters->value = BT_GATT_CCC_NOTIFY;
	parameters->notify = func;
	parameters->value_handle = descriptor->handle;
	parameters->ccc_handle = ccc_descriptor->handle;
	return 0;
}

/*
 * Get GATT read parameters
 * 
 * @param discovery: 	pointer to the discovery data received after calling gatt_discover_services(...)
 * @param uuid: 		characteristic's uuid
 * @param func: 		callback function for the read
 * @param parameters: 	read parameters to be filled, must be statically created
 */ 
int gatt_get_subscribe_parameters(struct bt_gatt_dm *discovery, struct bt_uuid* uuid, bt_gatt_read_func_t func, struct bt_gatt_read_params* parameters)
{
	// Get the characteristic and descriptors
	const struct bt_gatt_attr* characteristic = bt_gatt_dm_char_by_uuid(discovery, uuid);
	if (!characteristic) {
		printk("Missing characteristic in discovery data.\n");
		return -1;
	}
	const struct bt_gatt_attr* descriptor = bt_gatt_dm_desc_by_uuid(discovery, characteristic, uuid);
	if (!descriptor) {
		printk("Missing descriptor in discovery data.\n");
		return -1;
	}

	// Set up the read parameters
	parameters->handle_count = 1;
	parameters->single.offset = 0;
	parameters->func = func;
	parameters->single.handle = descriptor->handle;
	return 0;
}


/*
 * Discover a service
 * 
 * @param connection: pointer to the peripheral we want to discover its service
 * @param uuid: uuid of the service to be discovered
 * @param callback: all the callback methods for this discovery
 */ 
int gatt_discover_services(struct bt_conn *connection, struct bt_uuid* uuid, const struct bt_gatt_dm_cb *callback)
{
	int err = bt_gatt_dm_start(connection, uuid, callback, NULL);
	if (err) {
		printk("Could not start the discovery procedure, error code: %d\n", err);
	}
	return err;
}

/*
 * Subscribe to notifications on a characteristic
 * 
 * @param connection: pointer to the peripheral we want to discover its service
 * @param params: parameters of the subscribe request
 */ 
int gatt_subscribe_to_notifications(struct bt_conn *connection, struct bt_gatt_subscribe_params* params)
{
	int err = bt_gatt_subscribe(connection, params);
	if (err) {
		printk("Subscribe failed (err %d)\n", err);
	}
	return err;
}

/*
 * Read the value of a characteristic
 * 
 * @param connection: pointer to the peripheral we want to discover its service
 * @param params: parameters of the read request
 */ 
int gatt_read_characteristic(struct bt_conn *connection, struct bt_gatt_read_params* read_params)
{
	int err = bt_gatt_read(connection, read_params);
	if(err) {
		printk("Failed to read characteristic, err: %d\n", err);
	}
	return err;
}