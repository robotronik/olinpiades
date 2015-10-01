
int main() {

	//évite un reset automatique du microcontrôleur
	#if PIC_BUILD
		while(1);
	#endif

	return 0;
}
