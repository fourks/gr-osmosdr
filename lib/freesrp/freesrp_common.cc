#include "freesrp_common.h"

#include <boost/make_shared.hpp>

#include <arg_helpers.h>

using namespace FreeSRP;
using namespace std;

boost::shared_ptr<FreeSRP::FreeSRP> freesrp_common::_srp;

freesrp_common::freesrp_common(const std::string &args)
{
    dict_t dict = params_to_dict(args);

    if(!_srp)
    {
        try
        {
            _srp.reset(new FreeSRP::FreeSRP());
            cout << "Connected to FreeSRP" << endl;
        }
        catch(const ConnectionError& e)
        {
            cerr << "FreeSRP Error: " << e.what() << endl;
            throw runtime_error(e.what());
        }
    }
}

std::vector<std::string> freesrp_common::get_devices()
{
    std::vector<std::string> devices;

    try
    {
        FreeSRP::FreeSRP srp;

        string str;
        str = "freesrp=0,label='FreeSRP'";

        devices.push_back(str);
    }
    catch(const ConnectionError &err)
    {
        // No FreeSRP found.
    }

    return devices;
}

size_t freesrp_common::get_num_channels( void )
{
    return 1;
}

osmosdr::meta_range_t freesrp_common::get_sample_rates( void )
{
    osmosdr::meta_range_t sample_rates;
    sample_rates.push_back(osmosdr::range_t(2.18e5, 61.44e6, 1));

    return sample_rates;
}

osmosdr::freq_range_t freesrp_common::get_freq_range(size_t chan)
{
    osmosdr::meta_range_t freq_ranges;

    freq_ranges.push_back(osmosdr::range_t(7e7, 6e9, 2.4));

    return freq_ranges;
}


osmosdr::freq_range_t freesrp_common::get_bandwidth_range(size_t chan)
{
    //TODO: Verify bandwidth ranges

    osmosdr::meta_range_t sample_rates;
    sample_rates.push_back(osmosdr::range_t(2.18e5, 56e6, 1));

    return sample_rates;
}


double freesrp_common::set_freq_corr( double ppm, size_t chan )
{
    // TODO: Set DCXO tuning
    return 0;
}

double freesrp_common::get_freq_corr( size_t chan )
{
    // TODO: Get DCXO tuning
    return 0;
}