A property behaves like a class data member, but it has additional features accessible through the Meta-Object System.
Para permitir implementação com meta-objeto

'READ'
Uma função de acesso READ é requerida se não foi declarada uma variável MEMBER.
Serve para ler o valor da propriedade.
Idealmente, usasse uma função const que retorna o tipo da propriedade ou uma referência const.

'WRITE'
Uma função de acesso WRITE é opcional.
É para setar o valor da propriedade
Deve retornar void e tomar exatamente um argumento, o tipo da propriedade ou referência do tipo.

