QObject *parent;
...
QString program = "./path/to/Qt/examples/widgets/analogclock";
QStringList arguments;
arguments << "-style" << "fusion";

QProcess *myProcess = new QProcess(parent);
myProcess->start(program, arguments);

QProcess entra no estado Starting
Quando começa, entra no estado Running e emite sinal started()
Quando acaba, entra no estado NotRunning inicial e emite sinal finished()
Se um erro ocorre, é emitido o sinal errorOcurred()

sinal finished() provê como argumentos o código de saída e o status de saída
chame error() pra saber o erro
chame state() pra saber o estado
