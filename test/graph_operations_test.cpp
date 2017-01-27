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

  EXPECT_EQ(vertex_map[Name("label1")][0]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[Name("label1")][1]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[Name("label2")][0]->GetAdjacentVertices().size(), 2);

  std::vector<Edge<int>*> edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), 3);
  vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 2);
  ASSERT_EQ(vertex_map[Name("label1")].size(), 2);
  ASSERT_EQ(vertex_map[Name("label2")].size(), 1);
  
  EXPECT_EQ(vertex_map[Name("label1")][0]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[Name("label1")][1]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[Name("label2")][0]->GetAdjacentVertices().size(), 2);
  graph.RemoveLastNVertices(2);
  edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), 0);
  vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 1);
  ASSERT_EQ(vertex_map[Name("label1")].size(), 1);
  EXPECT_EQ(vertex_map[Name("label1")][0]->GetAdjacentVertices().size(), 0);
}

TEST(GraphOps, GraphTraversal)
{
	/*
  Mapper mapper;
  kt_double range_threshold = 5.0;
  mapper.Initialize(range_threshold);
  Name label1("label1"), label2("label2");
  SensorManager* manager = SensorManager::GetInstance();
  manager->RegisterSensor(LaserRangeFinder::CreateLaserRangeFinder(LaserRangeFinderType::LaserRangeFinder_Custom, label1));
  manager->RegisterSensor(LaserRangeFinder::CreateLaserRangeFinder(LaserRangeFinderType::LaserRangeFinder_Custom, label2));
  RangeReadingsVector readings1;
  for(int i=0; i<181; i++)
  {
	  readings1.push_back(1.0);
  }
  mapper.setParamMinimumTravelHeading(kt_double(0.0));
  mapper.setParamMinimumTravelDistance(kt_double(0.0));
  ASSERT_TRUE(mapper.Process(new LocalizedRangeScan(label1, readings1)));
  ASSERT_TRUE(mapper.Process(new LocalizedRangeScan(label1, readings1)));
  ASSERT_TRUE(mapper.Process(new LocalizedRangeScan(label2, readings1)));

  LocalizedRangeScanVector vec = mapper.GetAllProcessedScans();
  mapper.GetGraph()->LinkScans(vec[0],vec[1],Pose2(), Matrix3());
*/


  MapperGraph graph(new Mapper(), kt_double(5.0));
  Name label1("label1");
  SensorManager* manager = SensorManager::GetInstance();
  manager->RegisterSensor(LaserRangeFinder::CreateLaserRangeFinder(LaserRangeFinderType::LaserRangeFinder_Custom, label1));
  RangeReadingsVector readings1 = {1.0,1.2}, readings2 = {2.0, 2.2}, readings3 = {3.0};
  graph.AddVertex(new LocalizedRangeScan(label1, readings1));
  graph.AddVertex(new LocalizedRangeScan(label1, readings2));
  graph.AddVertex(new LocalizedRangeScan(label1, readings3));
  std::map<Name, std::vector<Vertex<LocalizedRangeScan>*> > vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 1);
  ASSERT_EQ(vertex_map[label1].size(), 3);
  vertex_map[label1][0]->GetObject()->SetStateId(0);
  vertex_map[label1][1]->GetObject()->SetStateId(1);
  vertex_map[label1][2]->GetObject()->SetStateId(2);
  EXPECT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 0);
  EXPECT_EQ(vertex_map[label1][1]->GetAdjacentVertices().size(), 0);
  EXPECT_EQ(vertex_map[label1][2]->GetAdjacentVertices().size(), 0);
  
  kt_bool rIsNewEdge(true);
  graph.AddEdge(vertex_map[label1][0]->GetObject(), vertex_map[label1][1]->GetObject(), rIsNewEdge);
  EXPECT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 1);
  EXPECT_EQ(vertex_map[label1][1]->GetAdjacentVertices().size(), 1);
  EXPECT_EQ(vertex_map[label1][2]->GetAdjacentVertices().size(), 0);
  
  graph.AddEdge(vertex_map[label1][1]->GetObject(), vertex_map[label1][2]->GetObject(), rIsNewEdge);
  EXPECT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 1);
  EXPECT_EQ(vertex_map[label1][1]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[label1][2]->GetAdjacentVertices().size(), 1);
  
  graph.AddEdge(vertex_map[label1][0]->GetObject(), vertex_map[label1][2]->GetObject(), rIsNewEdge);
  EXPECT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[label1][1]->GetAdjacentVertices().size(), 2);
  EXPECT_EQ(vertex_map[label1][2]->GetAdjacentVertices().size(), 2);

  kt_double maxDistance = 1.0;
  LocalizedRangeScanVector lrsv;
  lrsv = graph.FindNearLinkedScans(vertex_map[label1][0]->GetObject(), maxDistance);
  EXPECT_EQ(lrsv.size(), 3);

  lrsv = graph.FindNearLinkedScans(vertex_map[label1][1]->GetObject(), maxDistance);
  EXPECT_EQ(lrsv.size(), 3);
  
  lrsv = graph.FindNearLinkedScans(vertex_map[label1][2]->GetObject(), maxDistance);
  EXPECT_EQ(lrsv.size(), 3);
  
  EXPECT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 2);
  graph.RemoveLastNVertices(2);
  std::vector<Edge<LocalizedRangeScan>*> edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), 0);
  vertex_map = graph.GetVertices();
  ASSERT_EQ(vertex_map.size(), 1);
  ASSERT_EQ(vertex_map[Name("label1")].size(), 1);

  ASSERT_EQ(vertex_map[label1][0]->GetAdjacentVertices().size(), 0);

  lrsv = graph.FindNearLinkedScans(vertex_map[label1][0]->GetObject(), maxDistance);
  EXPECT_EQ(lrsv.size(), 1);
  
  }
