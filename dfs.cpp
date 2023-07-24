// Dev: Vũ Nhật Quang
// Ứng dụng thuật toán DFS trong bài toán đổ nước thỏa mãn điều kiện cho trước
// Complexity: O(V+E) với V tương ứng với số lượng trạng thái bình nước có thể có và E tương ứng với số lượng cạnh trong đồ thị (số lần chuyẻn giữa các trạng thái trong bình)
// 24/07/2023 9:00PM
#include<bits/stdc++.h>
using namespace std;

//Cấu trúc State với 3 thuộc tính a, b, c tương ứng với 3 loại bình 10, 7, 4 lít
struct State {
    int a, b, c;
};

// Định nghĩa toán tử so sánh cho cấu trúc State để có thể sử dụng trong map
bool operator<(const State& x, const State& y) {
    if (x.a != y.a) return x.a < y.a; // So sánh thuộc tính a
    if (x.b != y.b) return x.b < y.b; // So sánh thuộc tính b
    return x.c < y.c; // So sánh thuộc tính c
}

// Khởi tạo mảng visited và đồ thị graph
bool visited[11][11][11]; 
//Mảng visited được sử dụng để đánh dấu các trạng thái bình đã được duyệt trong thuật toán DFS. 
//lượng nước tối đa cần là 11 ( 0 -> 10 )
map<State, vector<State>> graph;
// Đồ thị được lưu dưới dạng danh sách kề.
// Hàm dfs để duyệt đồ thị
void dfs(State u, State p) {
    if (visited[u.a][u.b][u.c]) return; // Nếu đã duyệt qua trạng thái bình này rồi thì bỏ qua
    visited[u.a][u.b][u.c] = true; // Đánh dấu trạng thái bình này đã được duyệt
    if (p.a != -1) graph[p].push_back(u); // Nếu không phải trạng thái ban đầu thì thêm vào đồ thị

    // Kiểm tra các trạng thái tiếp theo có thể đạt được và gọi hàm dfs cho chúng
    if (u.a > 0) { //Kiểm tra xem bình a có nước hay không.
        if (u.b < 7) dfs({ max(0, u.a - (7 - u.b)), min(7, u.b + u.a), u.c }, u);
//Nếu bình b chưa đầy (tối đa 7 lít), chuyển nước từ bình a sang b sao cho b đầy hoặc a hết. 
//Trạng thái mới sau khi chuyển nước sẽ được duyệt tiếp.
        if (u.c < 4) dfs({ max(0, u.a - (4 - u.c)), u.b, min(4, u.c + u.a) }, u);
        // Tương tự nhuư trên Tương tự, nếu bình c chưa đầy (dung tích tối đa là 4), chuyển nước từ bình a sang c
    }
    if (u.b > 0) {
        if (u.a < 10) dfs({ min(10, u.a + u.b), max(0, u.b - (10 - u.a)), u.c }, u);
        if (u.c < 4) dfs({ u.a, max(0, u.b - (4 - u.c)), min(4, u.c + u.b) }, u);
    }
    if (u.c > 0) {
        if (u.a < 10) dfs({ min(10, u.a + u.c), u.b, max(0, u.c - (10 - u.a)) }, u);
        if (u.b < 7) dfs({ u.a, min(7, u.b + u.c), max(0, u.c - (7 - u.b)) }, u);
    }
    // Các ý tưởng kiểm tra của các trạng thái bình nước tiếp theo tương tự như trên
}

int main() {
    // Ở bài toán này ta sẽ dùng lưu theo cấu trúc danh sách cạnh kề chứ không như lưu theo mảng 2 chiều 0,1.
    memset(visited, false, sizeof(visited)); // Khởi tạo mảng visited với giá trị false
    dfs({0, 7, 4}, {-1, -1, -1}); // Bắt đầu duyệt từ trạng thái (0, 7, 4)
    cout << "digraph {\n";
    for (auto& node : graph) { // Duyệt qua từng đỉnh trong đồ thị
        for (auto& child : node.second) { // Duyệt qua từng đỉnh con của đỉnh hiện tại
            cout << "  " << node.first.a << node.first.b << node.first.c << " -> " << child.a << child.b << child.c << ";\n"; // In ra cạnh từ đỉnh cha đến đỉnh con
            if (node.first.b == 2 || node.first.c == 2) { // Nếu đỉnh thỏa mãn điều kiện thì tô màu đỏ
                cout << "  " << node.first.a << node.first.b << node.first.c << " [label=\"(" << node.first.a << "," << node.first.b << "," << node.first.c << ")\", fillcolor=green, style=filled];\n";
            } else { // Nếu không thì không tô màu
                cout << "  " << node.first.a << node.first.b << node.first.c << " [label=\"(" << node.first.a << "," << node.first.b << "," << node.first.c << ")\"];\n";
            }
            cout << "  " << child.a << child.b << child.c << " [label=\"(" << child.a << "," << child.b << "," << child.c << ")\"];\n"; // In ra label cho đỉnh con
        }
    }
    cout << "}\n"; 
    return 0;
}