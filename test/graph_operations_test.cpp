#include <gtest/gtest.h>
#include <open_karto/Mapper.h>

using namespace karto;

TEST(GraphOps, RemoveLastNVertices)
{
  Graph<int> graph;
  graph.AddVertex(Name("label1"), new Vertex<int>(new int(1)));
  graph.AddVertex(Name("label1"), new Vertex<int>(new int(2)));
  graph.AddVertex(Name("label2"), new Vertex<int>(new int(3)));
  std::map<Name, std::vector<Vertex<int>*> > vertex_map = graph.GetVertices();
  graph.AddEdge(new Edge<int>(vertex_map[Name("label1")][0], vertex_map[Name("label1")][1]));
  graph.AddEdge(new Edge<int>(vertex_map[Name("label1")][1], vertex_map[Name("label2")][0]));
  graph.AddEdge(new Edge<int>(vertex_map[Name("label2")][0], vertex_map[Name("label1")][0]));

  std::vector<Edge<int>*> edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), 3);
  vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 2);
  ASSERT_EQ(vertex_map[Name("label1")].size(), 2);
  ASSERT_EQ(vertex_map[Name("label2")].size(), 1);

  graph.RemoveLastNVertices(2);
  edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), 0);
  vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 1);
  ASSERT_EQ(vertex_map[Name("label1")].size(), 1);
}
