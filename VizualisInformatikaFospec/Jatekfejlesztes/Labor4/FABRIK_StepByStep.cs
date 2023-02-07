using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FABRIK_StepByStep : MonoBehaviour
{
    public Transform target;
    public uint steps = 1;
    public bool updateJoints = false;
    public bool startFromInitialPose = false;
    public bool drawArm = true;
    public bool drawTarget = true;
    public bool drawPositionMarkers = true;
    public float markerSize = 0.1f;
    public float targetSize = 1.0f;

    List<Transform> joints;
    List<Renderer> armRenderers;
    Vector3[] positions;
    float[] distances;
    float totalDist;
    GameObject[] positionMarkers;
    Vector3 targetScaleOrig = new Vector3(1, 1, 1);

    // Collect all joints recursively, order in "joints" keeps the order in hierarchy
    void FindJoints(Transform t, ref List<Transform> joints, ref List<Renderer> armRenderers)
    {
        foreach (Transform child in t)
        {
            if (child.name.Contains("Joint"))
            {
                joints.Add(child);
            }
            if (child.name.Contains("Joint") || child.name.Contains("Bone"))
            {
                FindJoints(child.gameObject.transform, ref joints, ref armRenderers);
            }
            else
            {
                Renderer r = child.GetComponent<Renderer>();
                if (r != null)
                {
                    armRenderers.Add(r);
                }
            }
        }
    }

    void Start()
    {
        joints = new List<Transform>();
        armRenderers = new List<Renderer>();
        FindJoints(transform, ref joints, ref armRenderers);
        if (joints.Count == 0)
        {
            Debug.LogWarning("No joints found");
            enabled = false;
            return;
        }
        positions = new Vector3[joints.Count];
        distances = new float[joints.Count - 1];
        int i = 0;
        foreach(Transform joint in joints)
        {
            positions[i] = joint.position;
            ++i;
            //Debug.Log(joint.name + " -> " + joint.position);
        }

        positionMarkers = new GameObject[2 * positions.Length];
        for (int j = 0; j < positions.Length; ++j)
        {
            positionMarkers[j] = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            positionMarkers[j].GetComponent<Renderer>().material.color = Color.cyan;
        }

        if (target != null)
        {
            targetScaleOrig = target.localScale;
        }
    }

    bool Reachable()
    {
        return totalDist > Vector3.Distance(transform.position, target.transform.position);
    }

    void UpdateJoints()
    {
        int n = positions.Length;
        for (int i = 0; i < n-1; ++i)
        {
            Quaternion parentRotation = Quaternion.identity;
            if (i > 0) // has parent
            {
                parentRotation = joints[i - 1].rotation;
            }
            Vector3 baseDir = Vector3.up;
            Vector3 newDir = Quaternion.Inverse(parentRotation) * (positions[i + 1] - positions[i]);
            Vector3 rotAxis = Vector3.Cross(baseDir.normalized, newDir.normalized).normalized;
            float rotAngle = Vector3.SignedAngle(baseDir.normalized, newDir.normalized, rotAxis);
            if (rotAngle < 0.001)
            {
                joints[i].transform.localRotation = Quaternion.identity;
            }
            else
            {
                joints[i].transform.localRotation = Quaternion.AngleAxis(rotAngle, rotAxis);
            }
        }
    }

    void DrawPositionMarkers()
    {
        for (int i = 0; i < positions.Length; ++i)
        {
            positionMarkers[i] = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            positionMarkers[i].GetComponent<Renderer>().material.color = Color.cyan;
            positionMarkers[i].transform.localScale = new Vector3(markerSize, markerSize, markerSize);
            positionMarkers[i].transform.position = positions[i];
        }
    }

    void ResetArrays()
    {
        if (startFromInitialPose)
        {
            foreach (Transform joint in joints)
            {
                joint.localRotation = Quaternion.identity;
            }
        }
        for (int i = 0; i < positions.Length; ++i)
        {
            positions[i] = joints[i].position;
        }
        totalDist = 0;
        for (int j = 0; j < distances.Length; ++j)
        {
            distances[j] = Vector3.Distance(positions[j + 1], positions[j]);
            totalDist += distances[j];
        }
    }

    void Update()
    {
        if (target == null) return;

        ResetArrays();

        uint nSteps = steps;
        int n = positions.Length;
        Vector3 t = target.transform.position;
        if (Reachable())
        {
            Vector3 b = positions[0];
            float dif = Vector3.Distance(positions[n - 1], t);
            const float difThreshold = 0.01f;
            int iter = 0;
            while (dif > difThreshold && iter++ < 100 && nSteps > 1)
            {
                --nSteps;
                positions[n - 1] = t;
                for (int i = n - 2; i >= 0 && nSteps > 1; --i, --nSteps)
                {
                    float r = Vector3.Distance(positions[i + 1], positions[i]);
                    float lambda = distances[i] / r;
                    positions[i] = (1.0f - lambda) * positions[i + 1] + lambda * positions[i];
                }

                if (nSteps == 1) break;
                --nSteps;
                positions[0] = b;
                for (int i = 0; i < n - 1 && nSteps > 1; ++i, --nSteps)
                {
                    float r = Vector3.Distance(positions[i + 1], positions[i]);
                    float lambda = distances[i] / r;
                    positions[i + 1] = (1.0f - lambda) * positions[i] + lambda * positions[i + 1];
                }
            }
        }
        else
        {
            for (int i = 0; i < n - 1 && nSteps > 1; ++i, --nSteps)
            {
                float r = Vector3.Distance(t, positions[i]);
                float lambda = distances[i] / r;
                positions[i + 1] = (1.0f - lambda) * positions[i] + lambda * t;
            }
        }
        for (int i = 0; i < positions.Length; ++i)
        {
            positionMarkers[i].transform.localScale = new Vector3(markerSize, markerSize, markerSize);
            positionMarkers[i].transform.position = positions[i];
            positionMarkers[i].SetActive(drawPositionMarkers);
        }
        foreach (Renderer r in armRenderers) r.enabled = drawArm;
        target.GetComponent<Renderer>().enabled = drawTarget;
        if (updateJoints)
        {
            UpdateJoints();
        }
        target.localScale = targetScaleOrig * targetSize;
    }
}
