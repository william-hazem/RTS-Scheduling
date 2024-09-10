#include <iostream>
#include <stdio.h>
#include <math.h>
#include <json-c/json.h>
#include <vector>
#include <algorithm>
#include <fstream> 

struct Tarefa {
    const char* id;
    int periodo;
    int tempo_execucao;
    int prioridade;
};

// Função para comparar duas tarefas pelo período (para RM)
bool comparaTarefas(const Tarefa &t1, const Tarefa &t2) {
    return t1.periodo < t2.periodo; // Menor período tem maior prioridade
}

int main() {
    FILE *fp;
    struct json_object *parsed_json;
    struct json_object *tarefas;
    struct json_object *id;
    struct json_object *periodo;
    struct json_object *tempo_execucao;

    size_t n_tarefas;
    size_t i;
    
    double utilizacao_total = 0.0;  

    fp = fopen("tarefas.json", "r");
    if (fp == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo.\n");
        return 1;
    }

    char buffer[1024];
    fread(buffer, sizeof(buffer), 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "tasks", &tarefas);
    n_tarefas = json_object_array_length(tarefas);

    // Vetor para armazenar todas as tarefas
    std::vector<Tarefa> lista_tarefas;

    for (i = 0; i < n_tarefas; i++) {
        struct json_object *tarefa = json_object_array_get_idx(tarefas, i); 
        
        json_object_object_get_ex(tarefa, "id", &id);
        json_object_object_get_ex(tarefa, "period", &periodo);
        json_object_object_get_ex(tarefa, "execution_time", &tempo_execucao);

        // Calcular a utilização de cada tarefa (Ci/Ti) e somar à utilização total
        utilizacao_total += (double)json_object_get_int(tempo_execucao) / (double)json_object_get_int(periodo); 

        // Adiciona a tarefa ao vetor
        lista_tarefas.push_back({json_object_get_string(id), json_object_get_int(periodo), json_object_get_int(tempo_execucao), 0});
    }

    // Limite de utilização para escalonamento viável
    double limite = n_tarefas * (pow(2.0, 1.0 / n_tarefas) - 1.0);

    // Ordena as tarefas com base no período
    std::sort(lista_tarefas.begin(), lista_tarefas.end(), comparaTarefas);

    // Atribui prioridade com base na ordem de escalonamento 
    for (i = 0; i < n_tarefas; i++) {
        lista_tarefas[i].prioridade = i + 1; 
    }

    // Cria o objeto JSON de saída
    struct json_object *saida_json = json_object_new_object();
    struct json_object *schedulability = json_object_new_string(utilizacao_total <= limite ? "viable" : "non-viable");
    struct json_object *schedule_array = json_object_new_array();

    for (i = 0; i < n_tarefas; i++) {
        struct json_object *tarefa_json = json_object_new_object();
        json_object_object_add(tarefa_json, "id", json_object_new_string(lista_tarefas[i].id));
        json_object_object_add(tarefa_json, "priority", json_object_new_int(lista_tarefas[i].prioridade));
        json_object_array_add(schedule_array, tarefa_json);
    }

    json_object_object_add(saida_json, "schedulability", schedulability);
    json_object_object_add(saida_json, "suggested_schedule", schedule_array);

    // Gravar o JSON em um arquivo
    std::ofstream arquivo_saida("resultado_escalonamento.json");
    if (arquivo_saida.is_open()) {
        arquivo_saida << json_object_to_json_string_ext(saida_json, JSON_C_TO_STRING_PRETTY); // Formata o JSON com indentação
        arquivo_saida.close();
        std::cout << "Arquivo JSON de saída gerado com sucesso: resultado_escalonamento.json\n";
    } else {
        std::cerr << "Erro ao tentar criar o arquivo de saída.\n";
    }

    // Libera memória
    json_object_put(saida_json);
    json_object_put(parsed_json);

    return 0;
}
