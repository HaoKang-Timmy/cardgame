#ifndef CONST_H
#define CONST_H

enum MessageType{RoomStatus, NewParticipant, ParticipantLeft, StartgameServer, StartgameClient, ErrMessage};
enum SeatStatus{Free, Seated, Robot};
enum GameMessage{GameInit, FetchCardServer, FetchCardClient, EndFetchServer, EndFetchClient, EndRoundServer, EndRoundClient, NewRoundServer, NewRoundClient, EndGameServer, EndGameClient};
enum ErrCode{SeatFull, PlayerNotFull};
enum TYPEGAMES {_21_POINTS};

#endif // CONST_H
