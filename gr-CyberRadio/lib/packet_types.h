/***************************************************************************
 * \file PacketTypes.h
 *
 * \brief Defines data structures for handling VITA 49-formatted data packets.
 *
 * \author NH
 * \copyright Copyright (c) 2015 CyberRadio Solutions, Inc.
 *
 */

#ifndef INCLUDED_LIBCYBERRADIO_NDR651_PACKETTYPES_H_
#define INCLUDED_LIBCYBERRADIO_NDR651_PACKETTYPES_H_

#include <linux/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdint.h>

#define SAMPLES_PER_FRAME 1024

#define VRLP 0x56524c50
#define VEND 0x56454e44

/*!
 * \brief Provides programming elements for controlling CyberRadio Solutions products.
 */
namespace gr
{
	/*!
	 * \brief Provides programming elements for controlling the CyberRadio Solutions
	 *    NDR651 radio.
	 */
	namespace CyberRadio
	{

		/*!
		 * \brief VITA 49 frame header information.
		 */
		struct Vita49Header {
			uint32_t frameStart;     //!< Frame start word (ASCII string "VRLP")
			uint32_t frameSize:20;   //!< Frame size, in 32-bit words
			uint32_t frameCount:12;  //!< Frame Count
			uint16_t packetSize;     //!< Packet size, in 32-bit words
			uint16_t packetCount:4;  //!< Packet counter
			uint16_t TSF:2;          //!< Timestamp fractional field format
			uint16_t TSI:2;          //!< Timestamp integer field format
			uint16_t RSVD:2;         //!< RESERVED
			uint16_t T:1;            //!< Frame trailer present indicator
			uint16_t C:1;            //!< Class ID field present indicator
			uint16_t packetType:4;   //!< Packet type
			uint32_t streamId;       //!< Stream ID
			/*!
			 * \brief Class ID Field Part 1
			 *
			 * Contains the Organizationally Unique Identifier (OUI).
			 */
			uint32_t classId1;
			/*!
			 * \brief Class ID Field Part 2
			 *
			 * Bits 16-31 contain the Information Class Code (ICC).
			 * Bits 0-15 contain the Packet Class Code (PCC).
			 */
			uint32_t classId2;
			uint32_t timeSeconds;    //!< Timestamp integer field
			uint32_t timeFracSecMSB; //!< Timestamp fractional field, MSW
			uint32_t timeFracSecLSB; //!< Timestamp fractional field, LSW
		} __attribute__((packed));
		
		struct Vita49Header_NoClassId {
			uint32_t frameStart;     //!< Frame start word (ASCII string "VRLP")
			uint32_t frameSize:20;   //!< Frame size, in 32-bit words
			uint32_t frameCount:12;  //!< Frame Count
			uint16_t packetSize;     //!< Packet size, in 32-bit words
			uint16_t packetCount:4;  //!< Packet counter
			uint16_t TSF:2;          //!< Timestamp fractional field format
			uint16_t TSI:2;          //!< Timestamp integer field format
			uint16_t RSVD:2;         //!< RESERVED
			uint16_t T:1;            //!< Frame trailer present indicator
			uint16_t C:1;            //!< Class ID field present indicator
			uint16_t packetType:4;   //!< Packet type
			uint32_t streamId;       //!< Stream ID
			uint32_t timeSeconds;    //!< Timestamp integer field
			uint32_t timeFracSecMSB; //!< Timestamp fractional field, MSW
			uint32_t timeFracSecLSB; //!< Timestamp fractional field, LSW
		} __attribute__((packed));


		/*!
		 * \brief VITA 49 frame payload information.
		 */
		struct IqPayload {
			int16_t samples[2*SAMPLES_PER_FRAME];  //!< Interleaved I and Q samples
		} __attribute__((aligned));

		/*!
		 * \brief VITA 49 frame trailer information.
		 */
		struct Vita49Trailer {
			uint32_t frameEnd;          //!< Frame end word (ASCII string "VEND")
		} __attribute__((packed));

		/*!
		 * \brief VITA 49 transmit-over-UDP frame information.
		 */
		struct Ndr308Frame {
			struct Vita49Header v49;    //!< VITA 49 frame header
			struct IqPayload IQ;     //!< VITA 49 payload
			struct Vita49Trailer vend;  //!< VITA 49 frame trailer
		} __attribute__((aligned));

	}

}

#endif /* INCLUDED_LIBCYBERRADIO_NDR651_PACKETTYPES_H_ */
