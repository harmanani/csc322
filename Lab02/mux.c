int mux(short In1, short In2, short Sel)
{

	int Out;

	if (Sel == 0)
		Out = In1;
	else
		Out = In2;
	return(Out);
}