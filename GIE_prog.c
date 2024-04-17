
void GIE_vEnableGlobalInterrupt()
{
	__asm volatile("SEI");
}


void GIE_vDisableGlobalInterrupt()
{
	__asm volatile("CLI");
}