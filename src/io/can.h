#ifndef QT_DEMO_CAN_H
#define QT_DEMO_CAN_H

#include <optional>
#include "../shared/types.h"
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>

enum CanConnectionError {
	SocketError,
	BindError
};

enum CanReadError {
	ReadInterfaceNotCreated,
	SocketReadError,
	IncompleteCanFrame
};

enum CanWriteError {
	WriteInterfaceNotCreated,
	SocketWriteError,
};

Result<std::monostate, CanConnectionError> Can_Init();

Result<can_frame, CanReadError> Can_Read();

Result<std::monostate, CanWriteError> Can_Write();

#endif //QT_DEMO_CAN_H
