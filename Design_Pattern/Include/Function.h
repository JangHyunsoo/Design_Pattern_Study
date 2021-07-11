#pragma once
#include "Mecro.h"

template<typename T>
void Safe_Delete_VecList(T& p) {
	auto iterEnd = p.end();

	for (auto iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE((*iter));
	}

	p.clear();
}


template<typename T>
void Safe_Delete_Map(T& p) {
	auto iterEnd = p.end();

	for (auto iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE(iter->second);
	}

	p.clear();
}