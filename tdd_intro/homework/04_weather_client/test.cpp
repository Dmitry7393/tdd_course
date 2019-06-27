/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

/*
Architecture:
1. class FakeWeatherServer, that inherited from IWeatherServer
   FakeWeatherServer will contain map with hardcoded weather data
2. class WeatherParser, that will parse raw string with weather data
   method getWeather should return object Weather
3. class WeatherClient, inherited from IWeatherClient
   vector<Weather> getWeatherDataForDay(IWeatherServer& server, const std::string& date) returns
   array with all weather data for the day

Test plan
1. test getWeather("20;181;5.1") -> Weather(20, 181, 5.1)

2. test getWeather("31;109;4.0") -> Weather(31, 109, 4.0)

3. test getWeatherDataForDay
   "31.08.2018" -> vector<Weather> weatherData = { Weather(20, 181, 5.1),
                                                   Weather(23, 204, 4.9),
                                                   Weather(33, 193, 4.3),
                                                   Weather(26, 179, 4.5)
                                                 }
4. test getWeatherDataForDay
   "02.09.2018" -> vector<Weather> weatherData = { Weather(21, 158, 3.8),
                                                   Weather(25, 201, 3.5),
                                                   Weather(34, 258, 3.7),
                                                   Weather(27, 299, 4.0)
                                                 }
5. test GetAverageTemperature for 31.08.2018
   Expected result: 25.5
6. test GetMinimumTemperature for 31.08.2018
   Expected result: 20
7. test GetMaximumTemperature for 31.08.2018
   Expected result: 33
8. test GetAverageWindDirection for 31.08.2018
   Expected result: 189.25
9. test GetMaximumWindSpeed for 31.08.2018
   Expected result: 5.1
10. test for GetAverageTemperature for 02.09.2018
    Expected result: 26.75
11. test for GetMaximumTemperature for 01.09.2018
    Expected result: 31
12. test for GetMaximumWindSpeed for 01.09.2018
    Expected result: 4.2
*/
struct Weather
{
    short temperature ;
    unsigned short windDirection;
    double windSpeed;
    bool operator==(const Weather& right) const
    {
        return temperature == right.temperature &&
               windDirection == right.windDirection &&
               std::abs(windSpeed - right.windSpeed) < 0.01;
    }
};

class WeatherParser
{
public:
    Weather getWeather(const std::string& weatherData)
    {
        Weather weather;

        std::stringstream test(weatherData);
        std::string segment;
        std::vector<std::string> elements;

        while(std::getline(test, segment, ';'))
        {
            elements.push_back(segment);
        }

        weather.temperature = std::stoi(elements[0]);
        weather.windDirection = std::stoi(elements[1]);
        weather.windSpeed = std::atof(elements[2].c_str());

      return weather;
    }
};

class FakeWeatherServer : public IWeatherServer
{
public:

    std::string GetWeather(const std::string& request) override
    {
        return m_FakeWeatherData[request];
    }

    ~FakeWeatherServer() { }

private:
    std::map<std::string, std::string> m_FakeWeatherData = {
            {"31.08.2018;03:00", "20;181;5.1"},
            {"31.08.2018;09:00", "23;204;4.9"},
            {"31.08.2018;15:00", "33;193;4.3"},
            {"31.08.2018;21:00", "26;179;4.5"},

            {"01.09.2018;03:00", "19;176;4.2"},
            {"01.09.2018;09:00", "22;131;4.1"},
            {"01.09.2018;15:00", "31;109;4.0"},
            {"01.09.2018;21:00", "24;127;4.1"},

            {"02.09.2018;03:00", "21;158;3.8"},
            {"02.09.2018;09:00", "25;201;3.5"},
            {"02.09.2018;15:00", "34;258;3.7"},
            {"02.09.2018;21:00", "27;299;4.0"}
    };

};


class WeatherClient : public IWeatherClient
{
public:
    std::vector<Weather> getWeatherDataForDay(IWeatherServer& server, const std::string& date)
    {
        std::vector<Weather> weatherData;
        const std::vector<std::string> times = {"03:00", "09:00", "15:00", "21:00"};

        for (int i = 0; i < times.size(); ++i)
        {
            std::string response = server.GetWeather(date + ";" + times[i]);
            weatherData.push_back(m_WeatherParser.getWeather(response));
        }

        return weatherData;
    }

    double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<Weather> weatherData = getWeatherDataForDay(server, date);
        int sum = 0;

        for (int i = 0; i < weatherData.size(); ++i)
        {
            sum += weatherData.at(i).temperature;
        }

        return (double) sum / weatherData.size();
    }

    double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<Weather> weatherData = getWeatherDataForDay(server, date);
        int minTemperature = weatherData.at(0).temperature;

        for (int i = 1; i < weatherData.size(); ++i)
        {
            if (weatherData.at(i).temperature < minTemperature)
            {
                minTemperature = weatherData.at(i).temperature;
            }
        }

        return minTemperature;
    }

    double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<Weather> weatherData = getWeatherDataForDay(server, date);
        int maxTemperature = weatherData.at(0).temperature;

        for (int i = 1; i < weatherData.size(); ++i)
        {
            if (weatherData.at(i).temperature > maxTemperature)
            {
                maxTemperature = weatherData.at(i).temperature;
            }
        }

        return maxTemperature;
    }

    double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        std::vector<Weather> weatherData = getWeatherDataForDay(server, date);
        int sum = 0;

        for (int i = 0; i < weatherData.size(); ++i)
        {
            sum += weatherData.at(i).windDirection;
        }

        return (double) sum / weatherData.size();
    }

    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        return 0;
    }

    ~WeatherClient()
    {

    }

private:
    WeatherParser m_WeatherParser;
};

TEST(getWeather, parseWeatherDataFor31_08)
{
    Weather weather = { 20, 181, 5.1 };

    WeatherParser parser;
    ASSERT_EQ(weather, parser.getWeather("20;181;5.1"));
}

TEST(getWeather, parseWeatherDataFor01_09)
{
    Weather weather {31, 109, 4.0 };
    WeatherParser parser;
    ASSERT_EQ(weather, parser.getWeather("31;109;4.0"));
}

TEST(getWeatherDataForDay, weatherDataFor31_08)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

    std::vector<Weather> expectedWeatherData = {
                                      {20, 181, 5.1},
                                      {23, 204, 4.9},
                                      {33, 193, 4.3},
                                      {26, 179, 4.5}
                                    };

   ASSERT_EQ(weatherClient.getWeatherDataForDay(fakeWeatherServer, "31.08.2018"), expectedWeatherData);
}

TEST(getWeatherDataForDay, weatherDataFor02_09)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

    std::vector<Weather> expectedWeatherData = {
                                                  {21, 158, 3.8},
                                                  {25, 201, 3.5},
                                                  {34, 258, 3.7},
                                                  {27, 299, 4.0}
                                               };

   ASSERT_EQ(weatherClient.getWeatherDataForDay(fakeWeatherServer, "02.09.2018"), expectedWeatherData);
}

TEST(GetAverageTemperature, averageTemperaturefor31_08)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

   ASSERT_EQ(weatherClient.GetAverageTemperature(fakeWeatherServer, "31.08.2018"), 25.5);
}

TEST(GetMinimumTemperature, minimumTemperatureFor31_08is20)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

   ASSERT_EQ(weatherClient.GetMinimumTemperature(fakeWeatherServer, "31.08.2018"), 20);
}

TEST(GetMaximumTemperature, maximumTemperatureFor31_08is33)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

   ASSERT_EQ(weatherClient.GetMaximumTemperature(fakeWeatherServer, "31.08.2018"), 33);
}

TEST(GetAverageWindDirection, averageWindDirectionFor31_08is189_25)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

    ASSERT_EQ(weatherClient.GetAverageWindDirection(fakeWeatherServer, "31.08.2018"), 189.25);
}

TEST(GetMaximumWindSpeed, maximumWindSpeedFor31_08is5_1)
{
    FakeWeatherServer fakeWeatherServer;
    WeatherClient weatherClient;

    ASSERT_EQ(weatherClient.GetMaximumWindSpeed(fakeWeatherServer, "31.08.2018"), 5.1);
}
