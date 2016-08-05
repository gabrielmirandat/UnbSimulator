For example, if a user clicks a 'Close button', we probably want the 'windows close() function' to be called.

Sinais e slots são possíveis graças ao Qts 'meta-object system'.

Quando algo acontece, as vezes vc quer notificar outro.

Sinais e slots são uma alternativa à tecnica de callbacks, a diferença é que dão type-correctness aos argumentos.

Um 'sinal' é emitido quando um evento particular ocorre.
Widgets do Qt já tem vários sinais predefinidos, mas sempre podemos fazer subclasses de widgets para adicionar nossos 
próprios sinais à ele. 

Um 'slot' é uma função que é chamada em resposta à um sinal particular.
Widgets já tem vários slots predefinidos, mas é prática comum fazer subclasses de widgets e adicionar seus próprios 
slots para gerenciar sinais que esteja interessado. 

connect(Objeto1, sinal, Objeto2, slot);
//Conecta o sinal do objeto 1 ao slot do objeto 2

Sinais e Slots são type-safe. O tipo do sinal deve bater com o que o slot espera.
Sinais e slots tem baixo acoplamento. A classe não liga se não tem slot pra gerenciar um sinal que emitiu.
Qt assegura uma coisa. Se conectar um sinal a um slot, o slot será chamado com os parâmetros do sinal na hora certa.
A correspondência é completamente type-safe.

Toda classe que herda de QObject ou uma de suas subclasses (QWidget) já herdam sinais e slots. 

##########################################################################################################################Sinais
Sinais são emitidos por objetos quando estes mudam de estado, sendo isto interessante a outros objetos. 

Um sinal pode ser conectado à vários slots
Um slot pode ser conectado à vários sinais
É até possível conectar um sinal diretamente à outro sinal

Sinais são funções de acesso public e podem ser emitidas de qualquer lugar
Mas é altamente recomentado apenas emiti-los na classe que o define ou subclasses dela
Execução do código após 'emit' só ocorre uma vez que todos os slots associados tenham retornado--na ordem de conexão.

A situação é diferente com 'queued connections', código depois do emit continua imediatamente e slots executados depois.
Se vários slots conectados ao sinal, eles serão executados um atrás do outro, na ordem que foram conectados.

Sinais são automaticamente gerados pelo moc [Meta-Object Compiler] e NUNCA devem ser implementados no .cpp.
Não podem NUNCA ter tipo de retorno (use void)

Da experiência, sinais e slots são mais reusáveis se não tem tipos especiais de argumentos.

classe padrão moc
//--------------------------------
class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(QObject *parent = 0);
    ~MyClass();

signals:
    void mySignal();

public slots:
    void mySlot();
};
//--------------------------------

##########################################################################################################################Slots
Um slot é chamado quando um sinal conectado é emitido
São funções normais de C++ que podem ser chamadas normalmente

Um sinal emitido de uma instância de uma classe arbitrária pode fazer com que um slot privado de uma instância de outra 
classe não relacionada seja chamado

Uma prática útil é declarar slots virtual.

Toda classe com sinal/slot deve declarar Q_OBJECT no início e derivar de QObject

Com disconnect disconecta connected sinais e slots.

#######################################################################################################################Avançado
The QSignalMapper class is provided for situations where many signals are connected to the same slot and the slot needs 
to handle each signal differently.



//Minimal Sample//

//normal c++
class Counter
{
public:
    Counter() { m_value = 0; }

    int value() const { return m_value; }
    void setValue(int value);

private:
    int m_value;
};

//small QObject based with signal/slot
//Counter diz ao mundo todo que seu estado muda emitindo o sinal valueChanged()
//E tem um slot em que outros objetos podem se conectar com sinais
#include <QObject>

class Counter : public QObject
{
    Q_OBJECT

public:
    Counter() { m_value = 0; }

    int value() const { return m_value; }

public slots:
    void setValue(int value);

signals:
    void valueChanged(int newValue);

private:
    int m_value;
};

//exemplo de slot pra classe
void Counter::setValue(int value)
{
    if (value != m_value) { //previne ciclo infinito. Se a conecta com b e b com a
        m_value = value;
        emit valueChanged(value);
    }
}

//cria dois objetos Counter e conecta o sinal valueChanged() do primeiro ao 
//slot setValue() do segundo objeto
 Counter a, b;
    QObject::connect(&a, &Counter::valueChanged,
                     &b, &Counter::setValue);

    a.setValue(12);     // a.value() == 12, b.value() == 12
    b.setValue(48);     // a.value() == 12, b.value() == 48

//Real Example//
connect(sender, &QObject::destroyed, this, &MyObject::objectDestroyed);
connect(sender, SIGNAL(destroyed(QObject*)), this, SLOT(objectDestroyed(Qbject*)));
connect(sender, SIGNAL(destroyed()), this, SLOT(objectDestroyed(QObject*))); //runtime error

















