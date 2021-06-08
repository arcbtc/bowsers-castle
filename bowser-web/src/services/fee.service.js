const axios = require('axios');

let HOST = ''

/**
 * Get fees at the time of invocation.
 * @returns an object of the form:
 *    {
 *        "fastestFee": 33,
 *        "halfHourFee": 19,
 *        "hourFee": 11,
 *        "minimumFee": 1
 *    }
 */
async function getRecommendedFees() {
    const response = await axios.get(`${HOST}/api/v1/fees/recommended`);
    if (response.status !== 200) {
        throw new Error(`Cannot fetch fees from ${HOST}`);
    }
    return response.data;
}

function init(host) {
    if (!host) {
        throw new Error('Please provide the host value!');
    }
    HOST = host;
    return {
        getRecommendedFees
    }
}

module.exports = init;