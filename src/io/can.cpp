#include "can.h"
#include <cstring>

std::optional<int> CanInterface;

Result<std::monostate, CanConnectionError> Can_Init() {
	// Create a socket
	CanInterface = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (CanInterface < 0) {
		CanInterface = std::nullopt;
		return CanConnectionError::SocketError;
	}

	struct sockaddr_can addr{};
	struct ifreq ifr{};

	// Get interface index
	strcpy(ifr.ifr_name, "can0");
	ioctl(CanInterface.value(), SIOCGIFINDEX, &ifr);

	// Bind the socket to the CAN interface
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if (bind(CanInterface.value(), reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) < 0)
		return CanConnectionError::BindError;

	return std::monostate{};
}


Result<can_frame, CanReadError> Can_Read() {
	if (!CanInterface.has_value())
		return CanReadError::ReadInterfaceNotCreated;

	struct can_frame frame{};
	ssize_t readLengthBytes = read(CanInterface.value(), &frame, sizeof(struct can_frame));

	if (readLengthBytes < 0)
		return CanReadError::SocketReadError;
	if (readLengthBytes < sizeof(struct can_frame))
		return CanReadError::IncompleteCanFrame;
	return frame;
}

Result<std::monostate, CanWriteError> Can_Write() {
	if (!CanInterface.has_value())
		return CanWriteError::WriteInterfaceNotCreated;

	struct can_frame frame{};
	try {
		ssize_t nbytes = write(CanInterface.value(), &frame, sizeof(struct can_frame));
	} catch (...) {
		return CanWriteError::SocketWriteError;
	}
	return std::monostate{};
}