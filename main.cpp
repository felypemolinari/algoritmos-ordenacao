#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

/// Funções de ordenação

// Inserção direta
void InsercaoDireta(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Shellsort
void Shellsort(vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < arr.size(); i++) {
            int temp = arr[i];
            size_t j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Bolha
void Bubblesort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Quicksort
int Partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        Quicksort(arr, low, pi - 1);
        Quicksort(arr, pi + 1, high);
    }
}

// Seleção direta
void SelecaoDireta(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Heapsort
void Heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void Heapsort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

// Mergesort
void Merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++) left[i] = arr[l + i];
    for (int i = 0; i < n2; i++) right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void Mergesort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        Mergesort(arr, l, m);
        Mergesort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

// Função para medir o tempo de execução
double MeasureSort(void (*sortFunc)(vector<int>&), vector<int>& arr, int repetitions) {
    double totalDuration = 0.0;

    for (int i = 0; i < repetitions; i++) {
        auto start = high_resolution_clock::now();
        sortFunc(arr);
        auto end = high_resolution_clock::now();
        totalDuration += duration<double>(end - start).count();
    }

    return totalDuration / repetitions;
}

// Função para exibir o vetor
void PrintVector(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    int tamVetor, repeticoes, escolha, ordem;
    cout << "Digite o tamanho do vetor: ";
    cin >> tamVetor;

    vector<int> arr(tamVetor);

    cout << "Escolha a ordem inicial do vetor:\n"
         << "1. Melhor caso (ordenado)\n"
         << "2. Pior caso (ordenado reverso)\n"
         << "3. Aleatorio\n";
    cin >> ordem;

    if (ordem == 1) {
        for (int i = 0; i < tamVetor; i++) arr[i] = i + 1; // Melhor caso
    } else if (ordem == 2) {
        for (int i = 0; i < tamVetor; i++) arr[i] = tamVetor - i; // Pior caso
    } else if (ordem == 3) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < tamVetor; i++) arr[i] = dis(gen); // Aleatório
    } else {
        cout << "Opcao invalida!\n";
        return 1;
    }

    cout << "Digite a quantidade de repeticoes: ";
    cin >> repeticoes;

    cout << "Escolha o algoritmo de ordenacao:\n"
         << "1. Insertion Sort\n"
         << "2. Shell Sort\n"
         << "3. Bubble Sort\n"
         << "4. Quick Sort\n"
         << "5. Selection Sort\n"
         << "6. Heap Sort\n"
         << "7. Merge Sort\n";
    cin >> escolha;

    void (*sortFunc)(vector<int>&);
    switch (escolha) {
        case 1: sortFunc = InsercaoDireta; break;
        case 2: sortFunc = Shellsort; break;
        case 3: sortFunc = Bubblesort; break;
        case 4: sortFunc = [](vector<int>& a) { Quicksort(a, 0, a.size() - 1); }; break;
        case 5: sortFunc = SelecaoDireta; break;
        case 6: sortFunc = Heapsort; break;
        case 7: sortFunc = [](vector<int>& a) { Mergesort(a, 0, a.size() - 1); }; break;
        default: cout << "Opcao invalida!\n"; return 1;
    }

    cout << "Vetor inicial:\n";
    PrintVector(arr);

    double averageTime = MeasureSort(sortFunc, arr, repeticoes);

    cout << "Vetor ordenado:\n";
    PrintVector(arr);

    cout << "Tempo medio de execucao: " << averageTime << " segundos\n";

    return 0;
}
