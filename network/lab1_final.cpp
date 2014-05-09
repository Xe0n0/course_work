#include "sysinclude.h"
#include <deque>
using namespace std;

typedef enum { data,ack,nak } frame_kind;
typedef struct frame_head{
	frame_kind kind;
	unsigned int seq;
	unsigned int ack;
	unsigned char data[100];
};
typedef struct frame{
	frame_head head;
	unsigned int size;
};


extern void SendFRAMEPacket(unsigned char* pData, unsigned int len);

deque<frame> buffered_queue_1;	// buffered queue for slide window stop_and_wait
deque<frame> buffered_queue_2;	// buffered queue for slide window back_n_frame
deque<frame> sent_queue_2;		// sent packet is stored in this queue
deque<frame> buffered_queue_3;	// buffered queue for slide window choice_frame_resend
deque<frame> sent_queue_3;

#define WINDOW_SIZE_STOP_WAIT 1
#define WINDOW_SIZE_BACK_N_FRAME 4



/*
*  stop and wait protocol
*/
int stud_slide_window_stop_and_wait(char *pBuffer, int bufferSize, UINT8 messageType)
{
	if( messageType == MSG_TYPE_TIMEOUT ){
		frame f = buffered_queue_1.front();
		SendFRAMEPacket((unsigned char*)(&f), f.size);
	}
	else if( messageType == MSG_TYPE_SEND){
		frame f;
		memcpy((&f), pBuffer, sizeof(f));
		f.size = bufferSize;
		buffered_queue_1.push_back(f);
		if( buffered_queue_1.size() > WINDOW_SIZE_STOP_WAIT ){
			return 0;
		}
		else{
			SendFRAMEPacket( (unsigned char*)(&f), f.size );
		}
	}
	else if( messageType == MSG_TYPE_RECEIVE ){
		buffered_queue_1.pop_front();
		if( !buffered_queue_1.empty() ){
			frame f = buffered_queue_1.front();
			SendFRAMEPacket((unsigned char*)(&f), f.size);
		}
	}	
	else{
		cout<<"error messageType"<<endl;
	}
	return 0;
}

/*
* back n protocol
*/
int stud_slide_window_back_n_frame(char *pBuffer, int bufferSize, UINT8 messageType)
{
	if( messageType == MSG_TYPE_SEND ){
		frame f;
		memcpy(&f, pBuffer, sizeof(f));
		f.size = bufferSize;
		buffered_queue_2.push_back(f);
		while( sent_queue_2.size() < WINDOW_SIZE_BACK_N_FRAME && !buffered_queue_2.empty() ){
			frame ready2send = buffered_queue_2.front();
			sent_queue_2.push_back(ready2send);
			SendFRAMEPacket((unsigned char*)(&ready2send), ready2send.size);
			buffered_queue_2.pop_front();
		}
	}
	else if( messageType == MSG_TYPE_TIMEOUT ){
	
		unsigned int time_out_seq = *(unsigned int *)pBuffer;
		deque<frame>::const_iterator iter;

		for(iter = sent_queue_2.begin(); iter!=sent_queue_2.end(); iter++ ){
			frame resent = *iter;
			SendFRAMEPacket((unsigned char*)(&resent), resent.size);
		}
	}
	else if( messageType == MSG_TYPE_RECEIVE ){
		int ack = ntohl((*((frame*)pBuffer)).head.ack);

		deque<frame>::const_iterator iter;

		while (sent_queue_2.size() > 0 && ntohl(sent_queue_2.front().head.seq) <= ack) {
			
			sent_queue_2.pop_front();
		}
		while( sent_queue_2.size() < WINDOW_SIZE_BACK_N_FRAME && !buffered_queue_2.empty() ){
			frame ready2send = buffered_queue_2.front();
			sent_queue_2.push_back(ready2send);
			SendFRAMEPacket((unsigned char*)(&ready2send), ready2send.size);
			buffered_queue_2.pop_front();
		}
	} else cout << "wrong type" << endl;
	
	return 0;
}

/*
* window choice protocol
*/
int stud_slide_window_choice_frame_resend(char *pBuffer, int bufferSize, UINT8 messageType)
{
	if( messageType == MSG_TYPE_SEND ){
		frame f;
		memcpy((&f),pBuffer,sizeof(f));
		f.size = bufferSize;
		buffered_queue_3.push_back(f);
		while( sent_queue_3.size() < WINDOW_SIZE_BACK_N_FRAME && ! buffered_queue_3.empty() ){
			frame ready2send = buffered_queue_3.front();
			sent_queue_3.push_back(ready2send);
			SendFRAMEPacket((unsigned char*)(&ready2send), ready2send.size);
			buffered_queue_3.pop_front();
		}
	}
	else if( messageType == MSG_TYPE_RECEIVE ){
		frame f;
		memcpy((&f),pBuffer,sizeof(f));
		int receive_kind = ntohl(f.head.kind);

		if( receive_kind == nak ){

			int nak_seq = ntohl(f.head.ack);

			deque<frame>::iterator itr;
			for( itr=sent_queue_3.begin(); itr!=sent_queue_3.end(); itr++ ){
				int cur_seq = ntohl((*itr).head.seq);
				if( cur_seq == nak_seq ){
					break;
				}
			}
			frame resend_frame = *itr;
			SendFRAMEPacket((unsigned char*)(&resend_frame), resend_frame.size);
		}
		else{
			int ack_seq = ntohl(f.head.ack);
			deque<frame>::iterator itr;
			while (sent_queue_3.size() > 0 && ntohl(sent_queue_3.front().head.seq) <= ack_seq) {
			
				sent_queue_3.pop_front();
			}

			while(sent_queue_3.size() < WINDOW_SIZE_BACK_N_FRAME && ! buffered_queue_3.empty() ){
				frame ready2send = buffered_queue_3.front();
				sent_queue_3.push_back(ready2send);
				SendFRAMEPacket((unsigned char*)(&ready2send), ready2send.size);
				buffered_queue_3.pop_front();
			}
		}
	}
	return 0;
}
