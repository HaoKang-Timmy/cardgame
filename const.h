#ifndef CONST_H
#define CONST_H

enum MessageType{RoomStatus, NewParticipant, ParticipantLeft, StartgameServer, StartgameClient, ErrMessage};
enum SeatStatus{Free, Seated, Robot};
enum GameMessage{GameInit, FetchCardServer, FetchCardClient, EndRoundServer, EndRoundClient, EndGame};
enum ErrCode{SeatFull, PlayerNotFull};
enum TYPEGAMES {_21_POINTS};

#endif // CONST_H
