/*
// additional methods - hillclimbing
static std::vector<double> neigborhood(const double& number);
static double improve(const std::vector<double>& hood, improvement improvement_type);

// heuristic algorithm
static outcome iterated_hillclimbing(const function& f, unsigned char dimension, improvement improvement_type)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = 0.0;

    unsigned int N = f.get_N();
    for (unsigned int i = 0; i < N; i++)
    {
        double canditate = f.run(dimension); // vc
        while (double temp = improve(neigborhood(canditate), improvement_type) < canditate)
            canditate = temp;

        if (canditate > local_minimum)
            local_minimum = canditate;

        // UX
        if (0 == i % 100)
            std::cout << i << "iterations.\n";
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds); // error

    return { local_minimum, milliseconds };
}

// execution parsing methods
static void analysis(const function& f, unsigned char dimension, improvement improvement_type);
static void run(const function& f);



/*

//------------------------------------------------
// methods:

static std::vector<double> neigborhood(const double& number)
{
    // first == number
    const bitstring original(number);
    unsigned char bits_number = original.get_size();

    std::vector<double> hood(bits_number + 1);
    hood[0] = number;

    for (unsigned char index_bit = 0; index_bit < bits_number; index_bit++)
    {
        bitstring copy(original);
        copy.negation(index_bit);

        double new_number = copy.convert();
        hood[index_bit + 1] = new_number;
    }

    return hood;
}

static double improve(const std::vector<double>& hood, improvement improvement_type)
{
    double original = hood.at(0);
    if (improvement::best == improvement_type)
    {
        for (const double& value : hood)
            if (value < original)
                original = value;

        return original;
    }

    if (improvement::first == improvement_type)
    {
        for (const double& value : hood)
            if (value < original)
            {
                original = value;
                break;
            }

        return original;
    }

    // worst
    bool first_execution = true;
    double better_value = original;
    for (const double& value : hood)
        if (value < original)
        {
            if (first_execution)
            {
                better_value = value;
                first_execution = false;
            }
            else if (value > better_value)
                better_value = value;
        }

    original = better_value;
    return original;
}

static void analysis(const function& f, unsigned char dimension, improvement improvement_type)
{
    // UX
    std::cout << "function: id " << f.get_id() << ", ";
    std::cout << (int)dimension << "-dimensional, using ";
    switch (improvement_type)
    {
    case improvement::best:
        std::cout << "best ";
        break;
    case improvement::first:
        std::cout << "first ";
        break;
    case improvement::worst:
        std::cout << "worst ";
        break;
    default:
        break;
    }

    std::cout << "improvement.\n\n";

    // act
    outcome sample_outcome[SAMPLE_NUMBER];

    for (unsigned char index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
        sample_outcome[index_sample] = iterated_hillclimbing(f, dimension, improvement_type);

    // print
    // for function dimension improvement type
    // time
    // best solution
    // average solution
    // worst solution

    // UX
    std::cout << "\n\n";
}

static void run(const function& f)
{
    analysis(f, 2, improvement::best);
    analysis(f, 2, improvement::first);
    analysis(f, 2, improvement::worst);

    analysis(f, 10, improvement::best);
    analysis(f, 10, improvement::first);
    analysis(f, 10, improvement::worst);
}

*/