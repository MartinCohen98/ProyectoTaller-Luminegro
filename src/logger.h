#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <string>

namespace Logger{
using namespace std;

	enum class Severidad{
		DEBUG,
		INFO,
		ERROR
	};

	//static const char* SeveridadStr[] = {"DEBUG", "INFO", "ERROR"};


	class Log{
	private:
		void loggear(string mensaje, string severidad);
		Severidad severidadMinima;
		string pathLoggeo;
	public:
		//Log(Severidad severidadMin, string path);
		Log(const string severidadMin);
		void Info(string mensaje);
		void Debug(string mensaje);
		void Error(string mensaje);
	};
}

#endif /* SRC_LOGGER_H_ */