using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.IO;
using System.Net.Http.Headers;
using System.Security.Cryptography;
using UnityEditor;
using UnityEngine;


[CustomEditor(typeof(ReadText))]
public class SceneLoader : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();
        if (GUILayout.Button("Save Button"))
        {
            string path = EditorUtility.SaveFilePanel("testfile", "","test", "level");
            StreamWriter writer = new StreamWriter(path, false);
            UnityEngine.GameObject[] objectList = FindObjectsOfType<UnityEngine.GameObject>();
            for (int i = 0; i < objectList.Length; i++)
            {
                
                if (objectList[i].GetComponent<ReadText>() == null && objectList[i].tag != "MainCamera")
                {
                    if (objectList[i].GetComponent<MeshFilter>().sharedMesh.name == "Cube")
                    {
                        writer.Write("Type: " + 1 + "\n");
                    }
                    else if (objectList[i].GetComponent<MeshFilter>().sharedMesh.name == "Plane")
                    {
                        writer.Write("Type: " + 2 + "\n");
                    }
                    else if (objectList[i].GetComponent<MeshFilter>().sharedMesh.name == "Sphere")
                    {
                        writer.Write("Type: " + 3 + "\n");
                    }
                    else if (objectList[i].GetComponent<MeshFilter>().sharedMesh.name == "Capsule")
                    {
                        writer.Write("Type: " + 4 + "\n");
                    }
                    else if (objectList[i].GetComponent<MeshFilter>().sharedMesh.name == "Cylinder")
                    {
                        writer.Write("Type: " + 5 + "\n");
                    }
                    writer.Write(objectList[i].name + "\n");
                    writer.Write("Position: " + objectList[i].transform.position.x + " " + objectList[i].transform.position.y + " " + objectList[i].transform.position.z + "\n");
                    writer.Write("Rotation: " + (objectList[i].transform.rotation.x * Mathf.Deg2Rad) * 100+ " " + (objectList[i].transform.rotation.y * Mathf.Deg2Rad)* 100 + " " + (objectList[i].transform.rotation.z * Mathf.Deg2Rad)* 100 + "\n");
                    writer.Write("Scale: " + objectList[i].transform.localScale.x + " " + objectList[i].transform.localScale.y + " " + objectList[i].transform.localScale.z + "\n");
                    if (objectList[i].GetComponent<Rigidbody>() != null) 
                    { 
                        writer.Write(1 + "\n");
                    }
                    else 
                    { 
                        writer.Write(0 + "\n");
                    }
                }
            }

                writer.Close();
        }
        if (GUILayout.Button("Load Scene"))
        {
            string path = EditorUtility.OpenFilePanel("testfile", "", "level");
            UnityEngine.GameObject[] objectList = FindObjectsOfType<UnityEngine.GameObject>();

            for (int i = 0; i < objectList.Length; i++)
            {
                if (objectList[i].GetComponent<ReadText>() == null && objectList[i].tag != "MainCamera")
                    DestroyImmediate(objectList[i]);
            }

            StreamReader reader = new StreamReader(path);
            int integer = 0;
            int primativeType = 0;
            float[] positions = new float[3];
            float[] rot = new float[3];
            float[] scale = new float[3];
            int rb = 0;
            string name = null;
            string type = reader.ReadLine();
            while (type != null)
            {
                if (integer == 0)
                {
                    char[] separators = { ' ' };
                    string[] strValues = type.Split(separators);
                    int.TryParse(strValues[1], out primativeType);

                }
                else if (integer == 1)
                {
                    name = type;
                }
                else if (integer == 2)
                {
                    
                    char[] separators = { ' ' };
                    string[] strValues = type.Split(separators);
                    float.TryParse(strValues[1], out positions[0]);
                    float.TryParse(strValues[2], out positions[1]);
                    float.TryParse(strValues[3], out positions[2]);
                }
                else if (integer == 3)
                {
                    char[] separators = { ' ' };
                    string[] strValues = type.Split(separators);
                    float.TryParse(strValues[1], out rot[0]);
                    float.TryParse(strValues[2], out rot[1]);
                    float.TryParse(strValues[3], out rot[2]);
                }
                else if (integer == 4)
                {
                    char[] separators = { ' ' };
                    string[] strValues = type.Split(separators);
                    float.TryParse(strValues[1], out scale[0]);
                    float.TryParse(strValues[2], out scale[1]);
                    float.TryParse(strValues[3], out scale[2]);
                }
                else if (integer == 5)
                {
                    int.TryParse(type, out rb);
                }
                integer++;
                if (integer > 5)
                {
                    integer = 0;
                    if (primativeType == 1)
                    {
                        UnityEngine.GameObject temp = UnityEngine.GameObject.CreatePrimitive(PrimitiveType.Cube);
                        temp.name = name;
                        temp.transform.position = new Vector3(positions[0],positions[1],positions[2]);
                        temp.transform.localScale = new Vector3(scale[0], scale[1], scale[2]);
                         Quaternion q = Quaternion.Euler(rot[0], rot[1], rot[2]);
                        temp.transform.rotation = q;
                        if(rb == 1)
                            temp.AddComponent<Rigidbody>();
                    }
                    else if (primativeType == 2)
                    {
                        UnityEngine.GameObject temp = UnityEngine.GameObject.CreatePrimitive(PrimitiveType.Plane);
                        temp.name = name;
                        temp.transform.position = new Vector3(positions[0], positions[1], positions[2]);
                        temp.transform.localScale = new Vector3(scale[0], scale[1], scale[2]);
                        Quaternion q = Quaternion.Euler(rot[0], rot[1], rot[2]);
                    }
                    else if (primativeType == 3)
                    {
                        UnityEngine.GameObject temp = UnityEngine.GameObject.CreatePrimitive(PrimitiveType.Sphere);
                        temp.name = name;
                        temp.transform.position = new Vector3(positions[0], positions[1], positions[2]);
                        temp.transform.localScale = new Vector3(scale[0], scale[1], scale[2]);
                        Quaternion q = Quaternion.Euler(rot[0], rot[1], rot[2]);
                        temp.transform.rotation = q;
                        if (rb == 1)
                            temp.AddComponent<Rigidbody>();
                    }
                    else if(primativeType == 4)
                    {
                        UnityEngine.GameObject temp = UnityEngine.GameObject.CreatePrimitive(PrimitiveType.Capsule);
                        temp.name = name;
                        temp.transform.position = new Vector3(positions[0], positions[1], positions[2]);
                        temp.transform.localScale = new Vector3(scale[0], scale[1], scale[2]);
                        Quaternion q = Quaternion.Euler(rot[0], rot[1], rot[2]);
                        temp.transform.rotation = q;
                        if (rb == 1)
                            temp.AddComponent<Rigidbody>();
                    }
                    else if (primativeType == 5)
                    {
                        UnityEngine.GameObject temp = UnityEngine.GameObject.CreatePrimitive(PrimitiveType.Cylinder);
                        temp.name = name;
                        temp.transform.position = new Vector3(positions[0], positions[1], positions[2]);
                        temp.transform.localScale = new Vector3(scale[0], scale[1], scale[2]);
                        Quaternion q = Quaternion.Euler(rot[0], rot[1], rot[2]);
                        temp.transform.rotation = q;
                        if (rb == 1)
                            temp.AddComponent<Rigidbody>();
                    }
                }
                type = reader.ReadLine();
            }

            reader.Close();
           
        }
    }

}
