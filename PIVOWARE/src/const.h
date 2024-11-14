#ifndef CONST_H
#define CONST_H
#ifdef _WIN32
#pragma once
#endif

#define MAX_CLIENT_BITS		5
#define MAX_CLIENTS			(1 << MAX_CLIENT_BITS)	// 5 bits == 32 clients ( int32 limit )

#define MAX_ENTITY_BITS		9
#define MAX_ENTITIES		(1 << MAX_ENTITY_BITS)	// 9 bits == 512 entities ( int32 limit )

#endif // CONST_H