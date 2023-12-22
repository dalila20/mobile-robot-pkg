#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chain.hpp>
#include <kdl/tree.hpp>
#include <kdl/frames_io.hpp>
#include <fstream>
#include <ros/ros.h>

void writeDOT(const KDL::Tree& kdl_tree, const std::string& filename) {
    std::ofstream dotfile(filename.c_str());
    if (!dotfile.is_open()) {
        std::cerr << "Erro ao criar o arquivo DOT." << std::endl;
        return;
    }

    dotfile << "digraph KDL_Tree {" << std::endl;

    for (auto const& segment_pair : kdl_tree.getSegments()) {
        const KDL::Segment& segment = segment_pair.second.segment;
        if (segment.getJoint().getType() != KDL::Joint::None) {
            const std::string& parent = segment_pair.first;
            const std::string& child = segment.getJoint().getName();
            dotfile << "  \"" << parent << "\" -> \"" << child << "\";" << std::endl;
        }
    }

    dotfile << "}" << std::endl;

    dotfile.close();
}

int main(int argc, char** argv) {
    
    // Inicializa o ROS (se necessário)
    ros::init(argc, argv, "urdf_to_kdl_tree");

    // Obtém o caminho do arquivo URDF do argumento de linha de comando
    const std::string urdf_file = "carro.urdf";

    // Carrega o URDF do arquivo
    KDL::Tree kdl_tree;
    if (!kdl_parser::treeFromFile(urdf_file, kdl_tree)) {
        ROS_ERROR("Falha ao carregar o URDF.");
        return 1;
    }

    // Escreve a árvore KDL em um arquivo DOT
    const std::string dot_file = "tree.dot";
    writeDOT(kdl_tree, dot_file);

    // Informa ao usuário sobre o arquivo DOT gerado
    std::cout << "Arquivo DOT gerado: " << dot_file << std::endl;

    return 0;
}
