#include"Key.h"



Key::Key() {

}

void Key::Update() {
	memcpy(m_key_list[1], m_key_list[0], sizeof(*m_key_list));
	GetKeyboardState(m_key_list[0]);
}


bool Key::Push(int nVirtKey) const {
	return TestBit(m_key_list[0][nVirtKey]);
}


bool Key::Pushing(int nVirtKey) const {
	return TestBit(m_key_list[0][nVirtKey]) && !TestBit(m_key_list[1][nVirtKey]);
}


bool Key::Exit(int nVirtKey) const {
	return !TestBit(m_key_list[0][nVirtKey]) && TestBit(m_key_list[1][nVirtKey]);
}

inline bool Key::TestBit(const BYTE k) const {
	return ((k & 0x80) != 0);
}