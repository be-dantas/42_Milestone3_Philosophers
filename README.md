# Milestone3 Philosophers

O projeto Philosophers da Escola 42 é uma simulação do clássico problema do Dining Philosophers, usado para ensinar concorrência e sincronização em programação.
Você precisa programar, em C, filósofos que comem, dormem e pensam, mas que compartilham garfos (recursos). Para comer, cada filósofo precisa de dois garfos, o que cria conflitos e risco de deadlock.

## 🎯 Proposta do projeto é ensinar a lidar com:

- Threads (ou processos)
- Mutexes e semáforos no bonus 
- Race conditions
- Deadlocks e starvation

## 🔧 Regras do Projeto

1. Deve simular que o filósofo: pegue os garfos, coma, durma e pense. Eles repetem esse ciclo até morrer ou até as regras de tempo acabarem.

2. Cada filósofo precisa de: 2 garfos (um à esquerda e um à direita) para comer.

3. O filósofo morre se ficar mais tempo que time_to_die sem comer.

6. A simulação termina quando algum filósofo morre, ou se todos comeram o número mínimo de vezes (se esse parâmetro existir).

7. Saída do programa deve ser clara, sem prints aleatórios

8. Input esperado (apenas numeros positivos): ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (opicional)]

## 🚀 Minha Solução

1. Structs
A divisão em quatro structs (input, filósofo, monitor e global) é adequada e ajuda na organização. Só cuide para não criar dependências desnecessárias entre elas.

2. Validação do input
Verificar letras, números negativos, zeros e quantidade correta de argumentos está correto. Tratar possíveis overflows seria um refinamento opcional.

3. Garfos e mutexes
Criar um mutex por garfo é o comportamento esperado. A ordem de travar os mutexes é crucial para evitar deadlock.

4. Threads dos filósofos
Criar uma thread por filósofo e executar o ciclo comer–dormir–pensar é o padrão. O uso de mutex para controlar o print também é necessário.

5. Monitor
Ter uma thread dedicada ao monitoramento do estado dos filósofos e de uma flag global é a abordagem correta para detectar mortes sem race conditions.

6. pthread_join
Usar pthread_join para garantir que todas as threads finalizem corretamente é obrigatório e está certo.

7. Destruição de mutexes
Finalizar todos os mutexes ao encerrar o programa é a prática correta e evita vazamentos.

## 🛠️ Como usar

Compilar:
```bash
make
```
```bash
./philo 5 800 200 200
```
