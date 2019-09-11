#ifndef SRC_LOGGER_
#define SRC_LOGGER_

#include <string>

namespace Logger{
using namespace std;

	enum class Severidad{
		DEBUG,
		INFO,
		ERROR
	};

	//static const char* SeveridadStr[] = {"DEBUG", "INFO", "WARNING","ERROR"};


	class Log{
	private:
		void loggear(string mensaje, string severidad);
		Severidad severidadMinima;
		string pathLoggeo;
	public:
		Log(Severidad severidadMin);
		void Info(string mensaje);
		void Debug(string mensaje);
		void Error(string mensaje);
	};
}

#endif /*SRC_LOGGER_*/
