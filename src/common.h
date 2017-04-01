#if defined(GENPERM) || defined(BENCH)
// input array
perm_t perm = Rand;		// random permutation
int modulo = 0;   		// zero means same as length
int use_seed = 0;  		// seed (default) or given seed
int seed;
#endif
int length = 1000;		// length of permutation / pre-reserved space

#if defined(RUNALG) || defined(BENCH)
// benchmark
int maxRepeat = 100;
int maxTime = 1;
timer_t timer;
stat_t stat;

// algorithm
char* name;
SortFun algtime;
SortFun algstat;
#endif

#ifdef RUNALG
int input_flag = 0;
int output_flag = 0;
#endif

// other
int verbose_flag = 0;
int help_flag = 0;


// command-line long options
struct option options[] = {
#if defined(GENPERM) || defined(BENCH)
    {"kind",    required_argument, 0, 'k'},
    {"modulo",  required_argument, 0, 'm'},
    {"seed",    required_argument, 0, 's'},
#endif
#if defined(RUNALG) || defined(BENCH)
    {"repeat",  required_argument, 0, 'r'},
    {"time",    required_argument, 0, 't'},
#endif
#ifdef RUNALG
    {"input",   no_argument, &input_flag, 1},
    {"output",  no_argument, &output_flag, 1},
#endif
    {"length",  required_argument, 0, 'l'},
    {"verbose", no_argument, &verbose_flag, 1},
    {"help",    no_argument, &help_flag, 1},
    {0, 0, 0, 0}
};


// command-line short options
#ifdef GENPERM
#define SHORTOPT "hvl:k:m:s:"
#endif
#ifdef RUNALG
#define SHORTOPT "hviol:r:t:"
#endif
#ifdef BENCH
#define SHORTOPT "hvl:k:m:s:r:t:"
#endif


void printUsage(const char *app_name) {
	// Usage
#if defined(RUNALG) || defined(BENCH)
    printf("Usage: %s alg\n", app_name);
    printAlgs("  alg: ");
#else
    printf("Usage: %s\n", app_name);
#endif
    // Options
    printf("\nOptions:\n");
#if defined(GENPERM) || defined(BENCH)
    printf("  -k perm, --kind perm\n\tInput permutation kind.\n");
    printPerms("\tperm: ");
#endif
    printf("  -l len, --length len\n\tLength of input permutation.\n");
#if defined(GENPERM) || defined(BENCH)
    printf("  -m mod, --modulo mod\n\tRange of values is from 0 to mod-1.\n\tIf mod is zero than the same as the length.\n");
    printf("  -s num, --seed num\n\tSeed for the random number generator.\n");
#endif
#if defined(RUNALG) || defined(BENCH)
    printf("  -r num, --repeat num\n\tMax number of repeates.\n");
    printf("  -t sec, --time sec\n\tMax benchmark time.\n");
#endif
#if defined(RUNALG)
    printf("  -i, --input\n\tPrint input array.\n");
    printf("  -o, --output\n\tPrint output array.\n");
#endif
    printf("  -v, --verbose\n\tPrint settings.\n");
    printf("  -h, --help\n\tPrint short help.\n");
}


void printSettings() {
#if defined(GENPERM) || defined(BENCH)
    printf("Input: kind=%s, length=%d, modulo=%d", perm2str(perm), length, modulo);
    if (use_seed) printf(", seed=%d\n", seed); else printf(", seed=rnd\n");
#endif
#if defined(RUNALG) || defined(BENCH)
    printf("Bench: maxRepeat=%d, maxTime=%d\n", maxRepeat, maxTime);
#endif    
}


void processArgs(int argc, char* argv[]) {
    while (1) {
        int option_index = 0;
        int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
        if (opt == -1) break;
        switch (opt) {
            case 0:
                if (options[option_index].flag != 0) break;
                break;
#if defined(GENPERM) || defined(BENCH)
            case 'k':
                perm = str2perm(optarg);
                break;
            case 'm':
                modulo = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                use_seed = 1;
                break;
#endif
#if defined(RUNALG) || defined(BENCH)
            case 'r':
                maxRepeat = atoi(optarg);
                break;
            case 't':
                maxTime = atoi(optarg);
                break;
#endif                
#if defined(RUNALG)
			case 'i':
                input_flag = 1;
                break;
			case 'o':
                output_flag = 1;
                break;
#endif                
            case 'l':
                length = atoi(optarg); 
                break;
			case 'v':
                verbose_flag = 1;
                break;
			case 'h':
				help_flag = 1;
                break;
            case '?':
                exit(3);
                break;
            default:
                abort();
        }
    }

    if (help_flag) {
        printUsage(argv[0]);
        exit(0);
    }

#if defined(GENPERM) || defined(BENCH)
    if (modulo <= 0) modulo = length;
#endif

    if (optind < argc) {
#if defined(RUNALG) || defined(BENCH)
        name = argv[optind];
        const SortInfo* si = findAlg(name);
        if (si == NULL) {
            fprintf(stderr, "Unknown sorting algorithm '%s'.\n", name);
            exit(2);
        }
        algtime = si->funtime;
        algstat = si->funstat;
    } else {
#endif    	
        printUsage(argv[0]);
        exit(1);
    }

}