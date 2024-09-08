#include <iostream>
#include <stdio.h>
#include <json-c/json.h>

int main() {

    FILE *fp;
    struct json_object *parsed_json;
    struct json_object *tarefas;
    struct json_object *tarefa;
    struct json_object *id;
    struct json_object *periodo;
    struct json_object *tempo_execucao;
    struct json_object *prioridade;

    size_t n_tarefas;
    size_t i;

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

    printf("Número de Tarefas: %lu\n", n_tarefas);

    for (i = 0; i < n_tarefas; i++) {
        tarefa = json_object_array_get_idx(tarefas, i);

        json_object_object_get_ex(tarefa, "id", &id);
        json_object_object_get_ex(tarefa, "period", &periodo);
        json_object_object_get_ex(tarefa, "execution_time", &tempo_execucao);
        json_object_object_get_ex(tarefa, "prioridade", &prioridade);

        printf("Tarefa %lu:\n", i+1);
        printf("  ID: %s\n", json_object_get_string(id));
        printf("  Período: %d\n", json_object_get_int(periodo));
        printf("  Tempo de Execução: %d\n", json_object_get_int(tempo_execucao));
        printf("  Prioridade: %d\n", json_object_get_int(prioridade));
    }

    json_object_put(parsed_json); // Libera a memória alocada pelo parsed_json
}