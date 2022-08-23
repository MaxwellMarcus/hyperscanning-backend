#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "statemachine.h"

StateMachine::StateMachine() {
}

void StateMachine::Interpret( char* buffer ) {
	while ( *buffer != '\0' ) {
		std::string name( buffer );
		buffer += name.size() + 1;
		char size = *buffer++;
		std::string value( buffer, size );
		buffer += value.size();

		auto it = std::find( StateNames.begin(), StateNames.end(), name );
		if ( it != StateNames.end() ) { 
			StateValues[ it - StateNames.begin() ] = value;
		}
		else {
			StateNames.push_back( name );
			StateValues.push_back( value );
		}
	}
}

void StateMachine::SetState( std::string name, std::string value ) {
	message += name;
	message.push_back( '\0' );
	message += value;
	message.push_back( '\0' );

	LocateState( name ).assign( value );
}

void StateMachine::SetState( std::string name, char* value ) {
	message += name;
	message.push_back( '\0' );
	message += value;
	message.push_back( '\0' );

	LocateState( name ).assign( value );
}

std::string& StateMachine::LocateState( std::string name ) {
	auto it = std::find( StateNames.begin(), StateNames.end(), name );
	if ( it != StateNames.end() ) {
		return StateValues[ it - StateNames.begin() ];
	}
	StateNames.push_back( name );
	StateValues.push_back( std::string() );
	return StateValues[ StateNames.size() - 1 ];
}

const char* StateMachine::GetState( std::string name ) {
	return LocateState( name ).c_str();
}

StateMachine::~StateMachine() {
}
