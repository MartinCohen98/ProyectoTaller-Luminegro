#include <string>

namespace Logger{
using namespace std;

	enum class Severidad{
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	//static const char* SeveridadStr[] = {"DEBUG", "INFO", "WARNING","ERROR"};


	class Log{
	private:
		void loggear(string mensaje, string severidad);
		Severidad severidadMinima;
		string pathLoggeo;
	public:
		//Log(Severidad severidadMin, string path);
		Log(Severidad severidadMin);
		void Info(string mensaje);
		void Debug(string mensaje);
		void Warning(string mensaje);
		void Error(string mensaje);
	};
}
