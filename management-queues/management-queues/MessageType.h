#pragma once
enum class MessageType
{
	M_GOT_REQ,
	MTS_ASK_FOR_IMAGES,
	STM_SEND_IMAGES_PROP,
	MTS_GIVE_THE_CHOSEN_IMAGE,
	STM_RESPONSE_TO_THE_CHOSEN_IMAGE,
	MTS_SEND_LOCATION,
	MTS_MOVE_OUT_OF_THIS_EREA,
	MTS_STOP_SEND_LOCATION,
	MTS_STOP_AT_PLACE,
	MTS_BACK_TO_STARTING_POINT,
	MTS_SEND_EVENTS,
	STM_GET_EVENTS,
	MTIP_REQ_FOR_REAL_MAP,
	MTS_REQ_FOR_PHOTO,
	STM_LOCATION,
	size
};

