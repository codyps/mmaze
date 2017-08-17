// The system componenets reset by this request are implimentation
// defined.
void armv6m_reset_system(void)
{
	// 0x05FA = VECTKEY
	// 3 = SYSRESETREQ
	AIRCR = 0x05FA << 16 | (1 << 3);
	for (;;)
		;
}


