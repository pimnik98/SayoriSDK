extern int(*main)(int, char**);	
// Possible initializations here.
void __init(int argc, char** argv) {
	main(argc, argv);
}
